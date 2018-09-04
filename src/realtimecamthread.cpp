#include "include/realtimecamthread.h"

using namespace std;
using namespace cv;

RealTimeCamThread::RealTimeCamThread(StereoImage *stereo, QObject *parent)
    : QThread(parent)
    ,m_stereo(stereo)
{
    close_img_viewer = false;
    visensor_Close_IMU_viewer = false;
    m_remapFlag = false;
    m_calibFlag = false;
    m_reconstructionFlag = false;
}

RealTimeCamThread::~RealTimeCamThread()
{
    delete m_stereo;
    m_stereo = 0;
}

bool RealTimeCamThread::SetInputDirectory(QString inputDirectory)
{
    if(inputDirectory.isEmpty())
    {
        std::cout<<"Did not choose any directory. "<<std::endl;
        return false;
    }

    m_fileDirectory = inputDirectory.toStdString();
    return true;
}

bool RealTimeCamThread::GetLoitorCalibParam(std::__cxx11::string pathOfLoitorCalibFile)
{
    cv::FileStorage fs;
    fs.open(pathOfLoitorCalibFile, cv::FileStorage::READ);

    // if failed to open a file
    if(!fs.isOpened())
    {
        std::cout<<"Failed to read file 'StereoCalib.yml'(loitor calib file). "<<std::endl;
        return false;
    }
    else
    {

        fs["P1"]>>m_loitorCalibParam.m_P1;
        fs["P2"]>>m_loitorCalibParam.m_P2;
        fs["Left_Mapping_1"]>>m_loitorCalibParam.m_Left_Mapping_1;
        fs["Left_Mapping_2"]>>m_loitorCalibParam.m_Left_Mapping_2;
        fs["Right_Mapping_1"]>>m_loitorCalibParam.m_Right_Mapping_1;
        fs["Right_Mapping_2"]>>m_loitorCalibParam.m_Right_Mapping_2;

        m_loitorCalibParam.m_f = m_loitorCalibParam.m_P1.at<double>(0,0);
        m_loitorCalibParam.m_cu = m_loitorCalibParam.m_P1.at<double>(0,2);
        m_loitorCalibParam.m_cv = m_loitorCalibParam.m_P1.at<double>(1,2);
        m_loitorCalibParam.m_baseline = -(m_loitorCalibParam.m_P2.at<double>(0,3)/m_loitorCalibParam.m_f);
        /*
        cv::Mat K_l, K_r, P_l, P_r, R_l, R_r, D_l, D_r;
        fs["LEFT.K"] >> K_l;
        fs["RIGHT.K"] >> K_r;

        fs["LEFT.P"] >> P_l;
        fs["RIGHT.P"] >> P_r;

        fs["LEFT.R"] >> R_l;
        fs["RIGHT.R"] >> R_r;

        fs["LEFT.D"] >> D_l;
        fs["RIGHT.D"] >> D_r;

        int rows_l = fs["LEFT.height"];
        int cols_l = fs["LEFT.width"];
        int rows_r = fs["RIGHT.height"];
        int cols_r = fs["RIGHT.width"];

        if(K_l.empty() || K_r.empty() || P_l.empty() || P_r.empty() || R_l.empty() || R_r.empty() || D_l.empty() || D_r.empty() ||
                rows_l==0 || rows_r==0 || cols_l==0 || cols_r==0)
        {
            cerr << "ERROR: Calibration parameters to rectify stereo are missing!" << endl;
            return -1;
        }

        cv::Mat M1l,M2l,M1r,M2r;
        cv::initUndistortRectifyMap(K_l,D_l,R_l,P_l.rowRange(0,3).colRange(0,3),cv::Size(cols_l,rows_l),CV_32F,M1l,M2l);
        cv::initUndistortRectifyMap(K_r,D_r,R_r,P_r.rowRange(0,3).colRange(0,3),cv::Size(cols_r,rows_r),CV_32F,M1r,M2r);

        m_loitorCalibParam.m_P1=P_l;
        m_loitorCalibParam.m_P2=P_r;
        m_loitorCalibParam.m_Left_Mapping_1=M1l;
        m_loitorCalibParam.m_Left_Mapping_2=M2l;
        m_loitorCalibParam.m_Right_Mapping_1=M1r;
        m_loitorCalibParam.m_Right_Mapping_2=M2r;

        m_loitorCalibParam.m_f = m_loitorCalibParam.m_P1.at<double>(0,0);
        m_loitorCalibParam.m_cu = m_loitorCalibParam.m_P1.at<double>(0,2);
        m_loitorCalibParam.m_cv = m_loitorCalibParam.m_P1.at<double>(1,2);
        m_loitorCalibParam.m_baseline = -(m_loitorCalibParam.m_P2.at<double>(0,3)/m_loitorCalibParam.m_f);
*/
        std::cout<<"Read file 'StereoCalib.yml'(loitor calib file) success(realtimethread)."<<std::endl;
    }

    m_calibFlag = true;
    fs.release();
    return true;
}

void RealTimeCamThread::run()
{
//    /************************ Start Cameras ************************/
//    visensor_load_settings("/home/dadaoii/camtest/Loitor_VISensor_Setups.txt");

//    int r = visensor_Start_Cameras();
//    if(r<0)
//    {
//        printf("Opening cameras failed...\r\n");
//        return;
//    }

//    /************************** Start IMU **************************/
//    /*
//    int fd=visensor_Start_IMU();
//    if(fd<0)
//    {
//        printf("visensor_open_port error...\r\n");
//        return;
//    }
//    printf("visensor_open_port success...\r\n");
//*/
//    /************************ ************ ************************/

//    cv::Mat img_left;
//    cv::Mat img_right;
//    cv::Mat img_tempL;
//    cv::Mat img_tempR;

//    img_left.create(cv::Size(752,480),CV_8U);
//    img_right.create(cv::Size(752,480),CV_8U);
//    img_left.data=new unsigned char[IMG_WIDTH_WVGA*IMG_HEIGHT_WVGA];
//    img_right.data=new unsigned char[IMG_WIDTH_WVGA*IMG_HEIGHT_WVGA];

//    unsigned char* loitorLeftImageData;
//    unsigned char* loitorRightImageData;

//    //there is a bug, see the line after " visensor_imudata paired_imu", when I comment out them, the program will crash
//    QImage tempLeftQImage(img_left.cols, img_left.rows, QImage::Format_Indexed8);
//    QImage tempRightQImage(img_right.cols, img_right.rows, QImage::Format_Indexed8);

//    while(!close_img_viewer)
//    {
//        //here will report a warning. cuz the function will get a struct but i do not need it.(a part of loitor)
//        visensor_imudata paired_imu = visensor_get_stereoImg((char *)img_left.data,(char *)img_right.data,left_stamp,right_stamp);

//        //bug
//        QImage tempLeftQImage(img_left.cols, img_left.rows, QImage::Format_Indexed8);
//        QImage tempRightQImage(img_right.cols, img_right.rows, QImage::Format_Indexed8);

//        // Set the color table (used to translate colour indexes to qRgb values)
//        tempLeftQImage.setColorCount(256);
//        tempRightQImage.setColorCount(256);
//        for(int i = 0; i < 256; i++)
//        {
//           tempLeftQImage.setColor(i, qRgb(i, i, i));
//           tempRightQImage.setColor(i, qRgb(i, i, i));
//        }
//        // Copy input Mat
//        uchar *pSrc = img_left.data;
//        for(int row = 0; row < img_left.rows; row ++)
//        {
//           uchar *pDest = tempLeftQImage.scanLine(row);
//           memcpy(pDest, pSrc, img_left.cols);
//           pSrc += img_left.step;
//        }
//        uchar *pSrc_ = img_right.data;
//        for(int row = 0; row < img_right.rows; row ++)
//        {
//           uchar *pDest_ = tempRightQImage.scanLine(row);
//           memcpy(pDest_, pSrc_, img_right.cols);
//           pSrc_ += img_right.step;
//        }
//        m_displayLeftImage = tempLeftQImage;
//        m_displayRightImage = tempRightQImage;

//        if(m_remapFlag)
//        {
//            remap(img_left, img_tempL,
//                  m_loitorCalibParam.m_Left_Mapping_1, m_loitorCalibParam.m_Left_Mapping_2,
//                  cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
//            remap(img_right, img_tempR,
//                  m_loitorCalibParam.m_Right_Mapping_1, m_loitorCalibParam.m_Right_Mapping_2,
//                  cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
//            QImage RtempLeftQImage(img_tempL.cols, img_tempL.rows, QImage::Format_Indexed8);
//            QImage RtempRightQImage(img_tempR.cols, img_tempR.rows, QImage::Format_Indexed8);
//            RtempLeftQImage.setColorCount(256);
//            RtempRightQImage.setColorCount(256);
//            for(int i = 0; i < 256; i++)
//            {
//               RtempLeftQImage.setColor(i, qRgb(i, i, i));
//               RtempRightQImage.setColor(i, qRgb(i, i, i));
//            }
//            uchar *pSrc__ = img_tempL.data;
//            for(int row = 0; row < img_tempL.rows; row ++)
//            {
//               uchar *pDest__ = RtempLeftQImage.scanLine(row);
//               memcpy(pDest__, pSrc__, img_tempL.cols);
//               pSrc__ += img_tempL.step;
//            }
//            uchar *pSrc___ = img_tempR.data;
//            for(int row = 0; row < img_tempR.rows; row ++)
//            {
//               uchar *Dest___ = RtempRightQImage.scanLine(row);
//               memcpy(Dest___, pSrc___, img_tempR.cols);
//               pSrc___ += img_tempR.step;
//            }
//            m_remapLeftImage = RtempLeftQImage;
//            m_remapRightImage = RtempRightQImage;

//            //std::cout<<poseMatrix<<std::endl;
//            //m_slam->TrackStereo(img_tempL,img_tempR,capturedTime);
//            //m_stereo->SetOrbPose(m_slam->SaveTrajectoryKITTI());
//            //std::cout<<(m_slam->SaveTrajectoryKITTI().back())<<std::endl;
//            //std::cout<<"======================================="<<std::endl;

//            if(m_reconstructionFlag)
//            {
//                double capturedTime = left_stamp.tv_sec%1000+(left_stamp.tv_usec*0.000001);
//                cv::Mat poseMatrix = m_slam->TrackStereo(img_tempL,img_tempR,capturedTime);
//                m_stereo->SetOrbPose(poseMatrix);

//                if((left_stamp.tv_usec-right_stamp.tv_usec)<10)
//                {
//                    double capturedTime = left_stamp.tv_sec%1000+(left_stamp.tv_usec*0.000001);

//                    //m_stereo->SetOrbPose(m_slam->TrackStereo(img_tempL,img_tempR,capturedTime));
//                    //std::cout<<m_slam->TrackStereo(img_tempL,img_tempR,capturedTime)<<std::endl;

//                    IplImage tempImageLeft = img_tempL;
//                    IplImage tempImageRight = img_tempR;

//                    IplImage* rectLeftIplImage = cvCloneImage(&tempImageLeft);
//                    IplImage* rectRightIplImage = cvCloneImage(&tempImageRight);

//                    //Copy two images to an object.
//                    //Get their data address first.
//                    cvGetRawData(rectLeftIplImage, &loitorLeftImageData);
//                    cvGetRawData(rectRightIplImage, &loitorRightImageData);
//                    //Copy data.
//                    m_stereo->SetStereoImage(loitorLeftImageData,  rectLeftIplImage->width, rectLeftIplImage->height,
//                                             rectLeftIplImage->widthStep, true,  capturedTime);
//                    m_stereo->SetStereoImage(loitorRightImageData, rectRightIplImage->width, rectRightIplImage->height,
//                                             rectRightIplImage->widthStep, false, capturedTime);

//                    cvReleaseImage(&rectLeftIplImage);
//                    cvReleaseImage(&rectRightIplImage);
//                    //usleep(200000);
//                }
//            }
//        }

// /*
//        if(close_img_viewer)
//        {
//            visensor_Close_Cameras();
//            visensor_Close_IMU();
//        }
//*/
//        if(!close_img_viewer)
//        {
//            m_pickedNewCamImage = false;
//            emit DetectNewCamImage();
//            while (!m_pickedNewCamImage) usleep(1000);
//        }

//    }
}
