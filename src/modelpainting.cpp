#include "include/modelpainting.h"

using namespace std;

//DRAWING_POINT_SIZE means the size of the painting points
#define DRAWING_POINT_SIZE 0.6
//LIMIT_NUM_OF_FARME means how much frame would be kept.
//TODO: make it can be changed in the main window.
#define LIMIT_NUM_OF_FARME 500

ModelPainting::ModelPainting(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers),parent)
{
    //pose of view(it should be named as screen view, unrelavent to the camera poses)
    //zoom is the depth of view, rotx/roty/rotz are the euler angles of xyz axis respectively, tx/ty/tz is the position
    //initialize them here, can be change when you want to have a different view

    m_currPose.zoom = -7;
    m_currPose.rotx = 180;
    m_currPose.roty = 0;
    m_currPose.rotz = 0;
    m_currPose.tx   = 0;
    m_currPose.ty   = 0;
    m_currPose.tz   = -1.5;

    m_prePose.zoom = -7;
    m_prePose.rotx = 180;
    m_prePose.roty = 0;
    m_prePose.rotz = 0;
    m_prePose.tx   = 0;
    m_prePose.ty   = 0;
    m_prePose.tz   = -1.5;

    m_farestPose.tx = 0;
    m_farestPose.ty = 10;
    m_farestPose.tz = 0;

    m_backgroundFlag = true;
    m_showCamFlag = true;
    m_followCamFlag = true;
    m_recordFlag = false;

    m_countPoseNum = 0;
    //m_recordNum = 0;
}

ModelPainting::~ModelPainting()
{
    clearAll();
}

void ModelPainting::clearAll()
{
    m_cams.clear();
    for (int32_t i=0; i<=(int32_t)m_glList.size(); i++)
    {
        glDeleteLists(m_glList[i],1);
    }
    m_glList.clear();
    m_poses.clear();
}

//=============================================================================//
//===========================Camera and points=================================//
//=============================================================================//

//get the homography matrix of current frame and add its camera pose into the map.
//s is the line width of the camera
void ModelPainting::AddCamera(libviso2_Matrix HomographyMatrix, float s)
{
    // Create list with points for this camera
    libviso2_Matrix C(4,10);
    C._val[0][0] = -0.5*s; C._val[1][0] = -0.5*s; C._val[2][0] = +1.0*s;
    C._val[0][1] = +0.5*s; C._val[1][1] = -0.5*s; C._val[2][1] = +1.0*s;
    C._val[0][2] = +0.5*s; C._val[1][2] = +0.5*s; C._val[2][2] = +1.0*s;
    C._val[0][3] = -0.5*s; C._val[1][3] = +0.5*s; C._val[2][3] = +1.0*s;
    C._val[0][4] = -0.5*s; C._val[1][4] = -0.5*s; C._val[2][4] = +1.0*s;
    C._val[0][5] =      0; C._val[1][5] =      0; C._val[2][5] =      0;
    C._val[0][6] = +0.5*s; C._val[1][6] = -0.5*s; C._val[2][6] = +1.0*s;
    C._val[0][7] = +0.5*s; C._val[1][7] = +0.5*s; C._val[2][7] = +1.0*s;
    C._val[0][8] =      0; C._val[1][8] =      0; C._val[2][8] =      0;
    C._val[0][9] = -0.5*s; C._val[1][9] = +0.5*s; C._val[2][9] = +1.0*s;
    for (int32_t i=0; i<10; i++)
    {
        C._val[3][i] = 1;
    }

    // add camera to list of cameras
    libviso2_Matrix C_ref = HomographyMatrix*C;
    Camera cam;
    for (int32_t i=0; i<10; i++)
    {
        for (int32_t j=0; j<3; j++)
        {
            cam.p[i][j] = C_ref._val[j][i];
        }
    }
    m_cams.push_back(cam);

    if(m_cams.size()>LIMIT_NUM_OF_FARME)
    {
        m_cams.pop_front();
    }
    updateGL();
}

//get the map points and push into the GL list
//p is the point struct
void ModelPainting::AddPoints(std::vector<Point3D> p)
{
    //GLES program
    //create display list
    int32_t gl_idx = glGenLists(1);
    m_glList.push_back(gl_idx);
    glNewList(gl_idx,GL_COMPILE);

    glPointSize(DRAWING_POINT_SIZE);
    glBegin(GL_POINTS);
    for (vector<Point3D>::iterator it=p.begin(); it!=p.end(); it++)
    {
        glColor3f(it->val,it->val,it->val);
        glVertex3f(it->x,it->y,it->z);
    }

    //If frame number bigger than the limit, then delete those old frame
    if(m_glList.size()>LIMIT_NUM_OF_FARME)
    {
        m_glList.pop_front();
    }

    // finish display list
    glEnd();
    glEnd();
    glEndList();

    updateGL();
}

//let the view follow camera when mapping
void ModelPainting::FollowCamera(libviso2_Matrix H)
{
    //CHECKBOX flag
    if(m_followCamFlag)
    {
        //number of maps, change a view every 4 frame now.
        m_countPoseNum++;
        if(m_countPoseNum%4 == 0)
        {

            //get the current pose matrix
            Pose curPose;
            curPose.tx = -H._val[0][3];
            curPose.ty = -H._val[1][3]+1;
            curPose.tz = -H._val[2][3];

            //calculate the euler angles
            //euler angle is connected to their rotation sequence
            float sy = sqrt(H._val[0][0] * H._val[0][0] +  H._val[1][0] * H._val[1][0] );
            bool singular = sy < 1e-6;
            float x, y, z;
            if (!singular)
            {
                x = atan2(H._val[2][1] , H._val[2][2]);
                y = atan2(-H._val[2][0], sy);
                z = atan2(H._val[1][0], H._val[0][0]);
            }
            else
            {
                x = atan2(-H._val[1][2], H._val[1][1]);
                y = atan2(-H._val[2][0], sy);
                z = 0;
            }

            curPose.rotx = -x*(180/M_PI)+190;
            curPose.roty = -y*(180/M_PI);
            curPose.rotz = -z*(180/M_PI);
            curPose.zoom = -10;

            //stepsize is the speed of moving view
            float step_size = 0.1;

            //pose1 is the previous view, pose2 is the view that going to move
            Pose pose1 = m_prePose;
            Pose pose2 = curPose;

            //get the scale(x,z) of the map, so that the view can go to the center in the ShowMap()
            if(abs(curPose.tx)>abs(m_farestPose.tx))
                m_farestPose.tx = curPose.tx;
            if(abs(curPose.tz)>abs(m_farestPose.tz))
                m_farestPose.tz = curPose.tz;

            //aviod 180 degree rotation when changing the view
            if(abs(pose1.rotx-pose2.rotx)>100)
            {
                pose1.rotx = pose2.rotx;
                pose1.roty = pose2.roty;
                pose1.rotz = pose2.rotz;
                updateGL();
            }

            //for record function, get the pose of view
            if(m_recordFlag)
            {
                m_poses.push_back(curPose);
            }

            //the anime of moving view
            for (float pos=0; pos<=1; pos+=step_size)
            {
                //have no idea about this pos2, guess is a nonlinear function to seperate a line into several different length line segment
                float pos2 = (1+sin(-M_PI/2+pos*M_PI))/2;
                m_currPose.zoom = pose1.zoom+(pose2.zoom-pose1.zoom)*pos2;
                m_currPose.rotx = pose1.rotx+(pose2.rotx-pose1.rotx)*pos2;
                m_currPose.roty = pose1.roty+(pose2.roty-pose1.roty)*pos2;
                m_currPose.rotz = pose1.rotz+(pose2.rotz-pose1.rotz)*pos2;
                m_currPose.tx   = pose1.tx  +(pose2.tx  -pose1.tx  )*pos2;
                m_currPose.ty   = pose1.ty  +(pose2.ty  -pose1.ty  )*pos2;
                m_currPose.tz   = pose1.tz  +(pose2.tz  -pose1.tz  )*pos2;
                updateGL();
                /*
                if(m_recordFlag)
                {
                    QImage img = this->grabFrameBuffer();
                    char filename[1024];
                    sprintf(filename,"%s%06d.png",m_recordDirectory.c_str(),m_recordNum++);
                    img.save(QString(filename));
                }
                */
            }
            m_prePose = m_currPose;
        }
    }
    updateGL();
}

//show the map and track after mapping
void ModelPainting::ShowMap()
{
    //the parameters to show the map finally
    m_farestPose.zoom = -200;
    m_farestPose.rotx = 270;
    m_farestPose.roty = 0;
    m_farestPose.rotz = 0;
    m_farestPose.tx = m_farestPose.tx/2;
    m_farestPose.ty = 10;
    m_farestPose.tz = m_farestPose.tz/2;

    Pose pose1 = m_currPose;
    Pose pose2 = m_farestPose;

    //if record, save the pose of final view
    if(m_recordFlag)
    {
        m_poses.push_back(m_farestPose);
    }

    //stepsize is the speed of moving view
    float step_size = 0.05;

    //the anime of moving view
    for (float pos=0; pos<=1; pos+=step_size)
    {
        float pos2 = (1+sin(-M_PI/2+pos*M_PI))/2;
        m_currPose.zoom = pose1.zoom+(pose2.zoom-pose1.zoom)*pos2;
        m_currPose.rotx = pose1.rotx+(pose2.rotx-pose1.rotx)*pos2;
        m_currPose.roty = pose1.roty+(pose2.roty-pose1.roty)*pos2;
        m_currPose.rotz = pose1.rotz+(pose2.rotz-pose1.rotz)*pos2;
        m_currPose.tx   = pose1.tx  +(pose2.tx  -pose1.tx  )*pos2;
        m_currPose.ty   = pose1.ty  +(pose2.ty  -pose1.ty  )*pos2;
        m_currPose.tz   = pose1.tz  +(pose2.tz  -pose1.tz  )*pos2;
        updateGL();
        /*
        if(m_recordFlag)
        {
            QImage img = this->grabFrameBuffer();
            char filename[1024];
            sprintf(filename,"%s%06d.png",m_recordDirectory.c_str(),m_recordNum++);
            img.save(QString(filename));
        }
        */
    }
    /*
    if(m_recordFlag)
    {
        std::cout << "Save .png files finished. " << std::endl;
        char command[1024];
        sprintf(command,"gnome-terminal -e /home/dadaoii/real_time_mapper/convert2video.sh");
        int system_status = system(command);
        if( system_status ) {};
    }
    */

    //show the added poses, here is show the total map and save it as a video
    if(m_recordFlag)
    {
        PlayPoses(true);
    }

}

//reinitialize the view
void ModelPainting::ResetView()
{
    m_currPose.zoom = -7;
    m_currPose.rotx = 180;
    m_currPose.roty = 0;
    m_currPose.tx   = 0;
    m_currPose.ty   = 0;
    m_currPose.tz   = -1.5;
    updateGL();
}

//add a pose of current view
void ModelPainting::AddPose()
{
    m_poses.push_back(m_currPose);
    std::cout << "Add a pose, exsiting poses number: " << m_poses.size() << std::endl;
}

//delete a added pose
void ModelPainting::DelPose()
{
    if (m_poses.size()>0) m_poses.pop_back();
    std::cout << "Delete a pose, exsiting poses number: " << m_poses.size() << std::endl;
}

//show the added poses as a anime
void ModelPainting::PlayPoses(bool saveVideo)
{
    //nothing
    int system_status = 0;

    //create a directory to save png files
    if(saveVideo)
    {
        createNewRecordDirectory();
    }

    //stepsize is the speed of moving view
    float step_size = 0.05;

    //the number of png files
    int num=0;

    //the anime of moving view
    for (int i=0; i<(int)m_poses.size()-1; i++)
    {
        Pose pose1 = m_poses[i];
        Pose pose2 = m_poses[i+1];

        if(m_recordFlag)
        {
            //aviod 180 degree rotation when changing the view
            if(abs(pose1.rotx-pose2.rotx)>100)
            {
                pose1.rotx = pose2.rotx;
                pose1.roty = pose2.roty;
                pose1.rotz = pose2.rotz;
                updateGL();
            }
        }

        for (float pos=0; pos<=1; pos+=step_size)
        {
            float pos2 = (1+sin(-M_PI/2+pos*M_PI))/2;
            m_currPose.zoom = pose1.zoom+(pose2.zoom-pose1.zoom)*pos2;
            m_currPose.rotx = pose1.rotx+(pose2.rotx-pose1.rotx)*pos2;
            m_currPose.roty = pose1.roty+(pose2.roty-pose1.roty)*pos2;
            m_currPose.rotz = pose1.rotz+(pose2.rotz-pose1.rotz)*pos2;
            m_currPose.tx   = pose1.tx  +(pose2.tx  -pose1.tx  )*pos2;
            m_currPose.ty   = pose1.ty  +(pose2.ty  -pose1.ty  )*pos2;
            m_currPose.tz   = pose1.tz  +(pose2.tz  -pose1.tz  )*pos2;
            updateGL();

            //save the view as png
            if(saveVideo)
            {
                QImage img = this->grabFrameBuffer();
                char filename[1024];
                sprintf(filename,"%s%06d.png",m_recordDirectory.c_str(),num++);
                img.save(QString(filename));
            }
        }
    }

    //run the script of FFmpeg to convert the png files to a video file
    if(saveVideo)
    {
        std::cout << "Save .png files finished. " << std::endl;
        char command[1024];
        sprintf(command,"gnome-terminal -e /home/dadaoii/real_time_mapper/convert2video.sh");
        system_status = system(command);
        if( system_status ) {};
        std::cout << "Successful make video. " << std::endl;
    }
}

////create a directory to save png files
void ModelPainting::createNewRecordDirectory()
{
    char buffer[1024];
    int system_status = 0;
    sprintf(buffer,"/home/dadaoii/mapper_dataset/PngFiles/");
    std::cout << "Creating record directory: " << buffer << std::endl;
    char cmd1[1024];
    char cmd2[1024];
    sprintf(cmd1,"rm -r %s",buffer);
    sprintf(cmd2,"mkdir %s",buffer);
    // Do nothing. Just for resolving the warning message.
    system_status =system(cmd1);
    if( system_status ) {};
    system_status = system(cmd2);
    if( system_status ) {};

    //m_recordNum = 0;
    m_recordDirectory = buffer;
}


//=============================================================================//
//===========================GL painting=======================================//
//=============================================================================//

void ModelPainting::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glClearColor(0,0,1,1);
}

void ModelPainting::paintGL()
{
    // clear screen & set matrices
    if (m_backgroundFlag)
    {
        glClearColor(1,1,1,1);
    }
    else
    {
        glClearColor(0,0,0,1);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // apply transformation
    glTranslatef(0.0, 0.0,m_currPose.zoom);
    glRotatef(m_currPose.rotx, 1.0, 0.0, 0.0);
    glRotatef(m_currPose.roty, 0.0, 1.0, 0.0);
    glRotatef(m_currPose.rotz, 0.0, 0.0, 1.0);
    glTranslatef(m_currPose.tx,m_currPose.ty,m_currPose.tz);

    // draw 3d points
    for (deque<GLuint>::iterator it=m_glList.begin(); it!=m_glList.end(); it++)
    {
        glCallList(*it);
    }

    if (m_showCamFlag)
    {
        // draw cameras
        glDisable(GL_DEPTH_TEST);
        glLineWidth(1);
        for (deque<Camera>::iterator it = m_cams.begin(); it!=m_cams.end(); it++)
        {
            glColor3f(1.0,0.0,0.0);
            glBegin(GL_LINE_STRIP);
            for (int32_t i=0; i<10; i++)
            {
                glVertex3f(it->p[i][0],it->p[i][1],it->p[i][2]);
            }
            glEnd();
        }

        // draw connection line
        glBegin(GL_LINE_STRIP);
        for (deque<Camera>::iterator it = m_cams.begin(); it!=m_cams.end(); it++)
        {
            glVertex3f(it->p[5][0],it->p[5][1],it->p[5][2]);
        }
        glEnd();
        glEnable(GL_DEPTH_TEST);
    }
}

void ModelPainting::resizeGL(int width, int height)
{
    int side = qMax(width, height);
    glViewport((width-side)/2,(height-side)/2,side,side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1,0.1,10000);
    glMatrixMode(GL_MODELVIEW);

    updateGL();
}

//=============================================================================//
//===========================MouseEvent========================================//
//=============================================================================//

void ModelPainting::mousePressEvent(QMouseEvent *event)
{
    m_lastPose = event->pos();
}

void ModelPainting::mouseMoveEvent(QMouseEvent *event)
{
    // compute deltas
    float dx = -event->x() + m_lastPose.x();
    float dy = +event->y() - m_lastPose.y();

    if (event->buttons() & Qt::LeftButton)
    {
        m_currPose.rotx += dy;
        m_currPose.roty += dx;
    }
    // right button => translation
    // To study: this part is about the computer graphics and 3d points.
    else if (event->buttons() & Qt::RightButton )
    {
        float rotx2 = m_currPose.rotx;
        if (rotx2<170) rotx2 = 90;
        if (rotx2>190) rotx2 = 270;
        float rx = rotx2*M_PI/180.0;
        float ry = m_currPose.roty*M_PI/180.0;

        libviso2_Matrix R = libviso2_Matrix::rotMatY(-ry)*libviso2_Matrix::rotMatX(-rx);

        libviso2_Matrix v(3,1);
        v._val[0][0] = dx;
        v._val[1][0] = dy;

        v = R*v;
        m_currPose.tx += 0.0025*m_currPose.zoom*v._val[0][0];
        m_currPose.ty += 0.0025*m_currPose.zoom*v._val[1][0];
        m_currPose.tz += 0.0025*m_currPose.zoom*v._val[2][0];
    }

    m_lastPose = event->pos();
    updateGL();
}

void ModelPainting::wheelEvent(QWheelEvent *event)
{
    if (event->delta()>0)
    {
        m_currPose.zoom *= 1.15;
    }
    else
    {
        m_currPose.zoom /= 1.15;
    }
    //std::cout<<m_currPose.zoom<<std::endl;
    updateGL();
}

void ModelPainting::keyPressEvent(QKeyEvent *event)
{
    float dx=0;
    float dy=0;

    switch (event->key())
    {
    case Qt::Key_W : dy=30; break;
    case Qt::Key_S : dy=-30; break;
    case Qt::Key_A : dx=-10; break;
    case Qt::Key_D : dx=10; break;
    }

    float rotx2 = m_currPose.rotx;
    if (rotx2<170) rotx2 = 90;
    if (rotx2>190) rotx2 = 270;
    float rx = rotx2*M_PI/180.0;
    float ry = m_currPose.roty*M_PI/180.0;

    libviso2_Matrix R = libviso2_Matrix::rotMatY(-ry)*libviso2_Matrix::rotMatX(-rx);

    libviso2_Matrix v(3,1);
    v._val[0][0] = dx;
    v._val[1][0] = dy;

    v = R*v;
    m_currPose.tx += 0.0025*m_currPose.zoom*v._val[0][0];
    m_currPose.ty += 0.0025*m_currPose.zoom*v._val[1][0];
    m_currPose.tz += 0.0025*m_currPose.zoom*v._val[2][0];

    updateGL();
}
