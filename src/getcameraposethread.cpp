#include "include/getcameraposethread.h"

//TODO: make it can be changed in the main window.
//the flag to run the libviso2 forcibly
#define RUN_WITH_THE_LIBVISO2_VO_MANUALLY 0

GetCameraPoseThread::GetCameraPoseThread(CalibrationParameters *calib, StereoImage *stereo, QObject *parent)
    : QThread(parent)
    ,m_calib(calib)
    ,m_stereo(stereo)
{
    VisualOdometryStereo::parameters visualOdomStereoParam;

    if (m_calib->CheckRunDataType() == m_calib->DADAO_DATASET_FLAG)
    {
        visualOdomStereoParam.calib.f = m_calib->m_dadaoCalibParam.m_f; // x focal length in pixels.
        visualOdomStereoParam.calib.cu = m_calib->m_dadaoCalibParam.m_cu; // principal point (u-coordinate) in pixels
        visualOdomStereoParam.calib.cv = m_calib->m_dadaoCalibParam.m_cv; // principal point (v-coordinate) in pixels
        visualOdomStereoParam.base  = m_calib->m_dadaoCalibParam.m_baseline; // baseline in meters
    }
    else if (m_calib->CheckRunDataType() == m_calib->KITTI_DATASET_FLAG)
    {
        visualOdomStereoParam.calib.f = m_calib->m_KittiCalibParam.m_f; // x focal length in pixels.
        visualOdomStereoParam.calib.cu = m_calib->m_KittiCalibParam.m_cu; // principal point (u-coordinate) in pixels
        visualOdomStereoParam.calib.cv = m_calib->m_KittiCalibParam.m_cv; // principal point (v-coordinate) in pixels
        visualOdomStereoParam.base  = m_calib->m_KittiCalibParam.m_baseline; // baseline in meters
    }
    else if (m_calib->CheckRunDataType() == m_calib->LOITOR_DATASET_FLAG)
    {
        visualOdomStereoParam.calib.f = m_calib->m_loitorCalibParam.m_f; // x focal length in pixels.
        visualOdomStereoParam.calib.cu = m_calib->m_loitorCalibParam.m_cu; // principal point (u-coordinate) in pixels
        visualOdomStereoParam.calib.cv = m_calib->m_loitorCalibParam.m_cv; // principal point (v-coordinate) in pixels
        visualOdomStereoParam.base  = m_calib->m_loitorCalibParam.m_baseline; // baseline in meters
    }

    m_visualOdomStereo = new VisualOdometryStereo( visualOdomStereoParam );

    m_stereoImage = 0;
    m_poseFileStatus = false;
    m_HomographyMatrix = libviso2_Matrix(4,4);
    m_HomographyMatrix.eye();
}

GetCameraPoseThread::~GetCameraPoseThread()
{
    delete m_visualOdomStereo;
    m_visualOdomStereo = 0;
    if (m_stereoImage!=0)
    {
        delete m_stereoImage;
        m_stereoImage = 0;
    }
}

void GetCameraPoseThread::SendImage(StereoImage::StereoImageParameters &s, bool poseFileStatus)
{
    if (m_stereoImage!=0)
    {
        delete m_stereoImage;
        m_stereoImage = 0;
    }

    m_stereoImage = new StereoImage::StereoImageParameters(s);
    m_poseFileStatus = poseFileStatus;
}

void GetCameraPoseThread::run()
{
#if RUN_WITH_THE_LIBVISO2_VO_MANUALLY
    int32_t dim[3] = {0};
    dim[0] = m_stereoImage->width;
    dim[1] = m_stereoImage->height;
    dim[2] = m_stereoImage->step;

    m_visualOdomStereo->process(m_stereoImage->I1, m_stereoImage->I2, dim, false);
    libviso2_Matrix H_inv = libviso2_Matrix::eye(4);
    libviso2_Matrix H = m_visualOdomStereo->getMotion();

    if (H_inv.solve(H))
    {
        m_HomographyMatrix = m_HomographyMatrix*H_inv;

        //For debug
        //std::cout<<m_HomographyMatrix<<std::endl;
        //std::cout<<"====================="<<std::endl;

        m_pickedNewCamPose = false;
        emit DetectNewCameraPose();
        while (!m_pickedNewCamPose) usleep(1000);
    }

#else
    if(!m_poseFileStatus)
    {
        //std::cout<<"Can get the pose information, running the VO from LibVISO2."<<std::endl;

        //orbslam2
        libviso2_Matrix tempM = libviso2_Matrix::eye(4);

        tempM._val[0][0] = m_stereoImage->m_orbPose.at<float>(0,0);
        tempM._val[0][1] = m_stereoImage->m_orbPose.at<float>(0,1);
        tempM._val[0][2] = m_stereoImage->m_orbPose.at<float>(0,2);
        tempM._val[0][3] = m_stereoImage->m_orbPose.at<float>(0,3);

        tempM._val[1][0] = m_stereoImage->m_orbPose.at<float>(1,0);
        tempM._val[1][1] = m_stereoImage->m_orbPose.at<float>(1,1);
        tempM._val[1][2] = m_stereoImage->m_orbPose.at<float>(1,2);
        tempM._val[1][3] = m_stereoImage->m_orbPose.at<float>(1,3);

        tempM._val[2][0] = m_stereoImage->m_orbPose.at<float>(2,0);
        tempM._val[2][1] = m_stereoImage->m_orbPose.at<float>(2,1);
        tempM._val[2][2] = m_stereoImage->m_orbPose.at<float>(2,2);
        tempM._val[2][3] = m_stereoImage->m_orbPose.at<float>(2,3);

        tempM._val[3][0] = 0;
        tempM._val[3][1] = 0;
        tempM._val[3][2] = 0;
        tempM._val[3][3] = 1;

        m_HomographyMatrix = tempM;

        m_pickedNewCamPose = false;
        emit DetectNewCameraPose();
        while (!m_pickedNewCamPose) usleep(1000);

    }
    else if (m_calib->CheckRunDataType() == m_calib->DADAO_DATASET_FLAG)
    {
        //get the current image index num, copy the current pose
        int index = m_stereo->m_frameindex;
        libviso2_Matrix tempM = libviso2_Matrix::eye(4);
        vector<float> tempV= m_stereo->m_dadaoPoses[index];
        float x=tempV[2],y=tempV[3],theta=-tempV[4];

        //build the homographyMatrix by current pose
        tempM._val[0][0] = cos(theta);
        tempM._val[0][1] = 0;
        tempM._val[0][2] = sin(theta);
        tempM._val[0][3] = -y;
        tempM._val[1][0] = 0;
        tempM._val[1][1] = 1;
        tempM._val[1][2] = 0;
        tempM._val[1][3] = 0;
        tempM._val[2][0] = -sin(theta);
        tempM._val[2][1] = 0;
        tempM._val[2][2] = cos(theta);
        tempM._val[2][3] = x;
        tempM._val[3][0] = 0;
        tempM._val[3][1] = 0;
        tempM._val[3][2] = 0;
        tempM._val[3][3] = 1;

        m_HomographyMatrix = tempM;
        //float sy = sqrt(tempM._val[0][0] * tempM._val[0][0] +  tempM._val[1][0] * tempM._val[1][0] );
        //float kkky = atan2(-tempM._val[2][0], sy);
        //std::cout<<-sin(theta)<<" "<<theta<<" "<<kkky<<" "<<asin(-tempM._val[2][0])<<std::endl;
    }
    else if (m_calib->CheckRunDataType() == m_calib->KITTI_DATASET_FLAG)
    {
        //get the current image index num, copy the current pose
        int index = m_stereo->m_frameindex;
        libviso2_Matrix tempM = libviso2_Matrix::eye(4);
        vector<float> tempV= m_stereo->m_kittiPoses[index];

        //build the homographyMatrix by current pose
        tempM._val[0][0] = tempV[0];
        tempM._val[0][1] = tempV[1];
        tempM._val[0][2] = tempV[2];
        tempM._val[0][3] = tempV[3];
        tempM._val[1][0] = tempV[4];
        tempM._val[1][1] = tempV[5];
        tempM._val[1][2] = tempV[6];
        tempM._val[1][3] = tempV[7];
        tempM._val[2][0] = tempV[8];
        tempM._val[2][1] = tempV[9];
        tempM._val[2][2] = tempV[10];
        tempM._val[2][3] = tempV[11];
        tempM._val[3][0] = 0;
        tempM._val[3][1] = 0;
        tempM._val[3][2] = 0;
        tempM._val[3][3] = 1;

        m_HomographyMatrix = tempM;
    }

    //For debug
    //std::cout<<m_HomographyMatrix<<std::endl;
    //std::cout<<"====================="<<std::endl;

    m_pickedNewCamPose = false;
    emit DetectNewCameraPose();
    while (!m_pickedNewCamPose) usleep(1000);

#endif
}
