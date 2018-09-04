#ifndef MODELPAINTING_H
#define MODELPAINTING_H

#include <GL/glew.h>
#include <QtGui/QWidget>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <deque>
#include <iostream>
#include <math.h>
#include "libviso2/src/timer.h"
#include "libviso2/src/matrix.h"

class ModelPainting : public QGLWidget
{
    Q_OBJECT
public:

    //default constructor
    ModelPainting(QWidget *parent = 0);
    ~ModelPainting();

    //the struct of 3d map points, xyz means the position, val means the grayscale of the point.
    struct Point3D
    {
        float x,y,z;
        float val;
        Point3D (float x,float y,float z,float val) : x(x),y(y),z(z),val(val) {}
    };

    //clear everything
    void clearAll ();

    //get the homography matrix of current frame and add its camera pose into the map.
    void AddCamera(libviso2_Matrix HomographyMatrix, float s);

    //get the map points and push into the GL list
    void AddPoints(std::vector<Point3D> p);

    //let the view follow camera when mapping
    void FollowCamera(libviso2_Matrix H);

    //show the map and track after mapping
    void ShowMap();

    //CHECKBOX: change the background color
    void SetBackgroundFlag(bool backgroundFlag) { m_backgroundFlag = backgroundFlag; updateGL(); }

    //CHECKBOX: show the pose and track of cameras
    void SetShowCamerasFlag(bool showCamFlag) { m_showCamFlag = showCamFlag; updateGL(); }

    //CHECKBOX: view follow the camera
    void SetFollowCameraFlag(bool followCamFlag) { m_followCamFlag = followCamFlag; updateGL(); }

    //CHECKBOX: record and make a video
    void SetRecordFlag(bool recordFlag){ m_recordFlag = recordFlag;}

    //reinitialize the view
    void ResetView();

    //add a pose of current view
    void AddPose();

    //delete a added pose
    void DelPose();

    //show the added poses
    void PlayPoses(bool saveVideo);

    //create a directory to save png files
    void createNewRecordDirectory();

protected:

    //OPENGL function
    //core function to draw the map
    //BUG: resizeGL does not work well
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    //mouse event to move the view manually
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:

    //camera
    struct Camera
    {
        float p[10][3];
    };

    //pose of view(it should be named as screen view, unrelavent to the camera poses)
    //zoom is the depth of view, rotx/roty/rotz are the euler angles of xyz axis respectively, tx/ty/tz is the position
    struct Pose
    {
        float  zoom;
        float  rotx,roty,rotz;
        float  tx,ty,tz;
    };
    //pose of current pose
    Pose   m_currPose;
    //pose of previous pose
    Pose   m_prePose;
    //pose of the farest(to the origin pose) pose
    Pose   m_farestPose;

    //containters to save cameras, maps and poses
    std::deque<Camera> m_cams;
    std::deque<GLuint> m_glList;
    std::vector<Pose> m_poses;

    //mouse event
    QPoint m_lastPose;

    //CHECKBOX: variables of flags
    bool   m_backgroundFlag;
    bool   m_showCamFlag;
    bool   m_followCamFlag;
    bool   m_recordFlag;

    //number of moving view
    int m_countPoseNum;
    //int m_recordNum;

    //directory to save the view of map
    //TODO: move it to mainwindow
    std::string m_recordDirectory;

signals:

public slots:
};

#endif // MODELPAINTING_H
