#include "include/readlocalfilethread.h"

#include "InfiniTAM/Engine/ImageSourceEngine.h"
#include "InfiniTAM/ITMLib/Engine/ITMMainEngine.h"
#include "InfiniTAM/Engine/UIEngine.h"


ReadLocalFileThread::ReadLocalFileThread(CalibrationParameters *calib, StereoImage *stereo, QObject *parent)
      : QThread(parent)
      ,m_calib(calib)
      ,m_stereo(stereo)
{
    m_poseFileExist = false;
    m_endReading = false;
}

ReadLocalFileThread::~ReadLocalFileThread()
{

}

bool ReadLocalFileThread::SetInputDirectory(QString inputDirectory)
{
    m_inputDirectory = inputDirectory;
    if(m_inputDirectory.isEmpty())
    {
        std::cout<<"Did not choose any directory. "<<std::endl;
        return false;
    }
    return true;
}

//===============================================================================================//

void ReadLocalFileThread::run()
{
    std::string inputDirectory = m_inputDirectory.toStdString();
    std::cout<< "The choesn dataset directory is " << inputDirectory << std::endl;

    //=====================================================================================//
    //=============================ReadDadao===============================================//
    //=====================================================================================//
    //Check whether read calib file successfully.
    //Dadao calib file will be check first.
    if(m_calib->GetDadaoCalibParam(inputDirectory + DADAO_CALIB_PATH))
    {
        m_dadaoPoseAndTimestampsFilePath = inputDirectory + DADAO_POSE_AND_TIMESTAMPS_FILE_PATH;
        m_dadaoImagePath = inputDirectory; 

        if(m_stereo->GetDadaoTimesAndPoses(m_dadaoPoseAndTimestampsFilePath))
        {
            //The flag of pose file.
            m_poseFileExist = true;
            std::cout<<"The image number of dataset is: "<<m_stereo->m_numOfDadaoImage<<std::endl;
            m_runningDataset = " / " + QString::number(m_stereo->m_numOfDadaoImage) + QString(160,' ') + "Now running Dadao Dataset.";
        }
        else
        {
            return;
        }
        //The speed of reading images.
//        int fps = 10;
        //Temporary address to send data.
        unsigned char* dadaoLeftImageData;
        unsigned char* dadaoRightImageData;
        cv::Mat m_tempL;
        cv::Mat m_tempR;
        //0 = left, 1 = right.
        DadaoImage m_dadaoImage[2];
        for(int32_t i=0; i<m_stereo->m_numOfDadaoImage; ++i)
        {
            //wait reconstruction
            while( StereoImage::loadWaitDisparity ) usleep(1);
            StereoImage::loadWaitDisparity = true;

            //Get left and right images.
            m_stereo->GetDadaoImages(m_dadaoImage, m_dadaoImagePath, i);

            remap(m_dadaoImage[0].m_rawImage, m_tempL,
                  m_calib->m_dadaoCalibParam.m_Left_Mapping_1, m_calib->m_dadaoCalibParam.m_Left_Mapping_2,
                  cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());
            remap(m_dadaoImage[1].m_rawImage, m_tempR,
                  m_calib->m_dadaoCalibParam.m_Right_Mapping_1, m_calib->m_dadaoCalibParam.m_Right_Mapping_2,
                  cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar());

            cv::Mat tempLeftMat;
            cv::Mat tempRightMat;

            m_tempL(m_calib->m_dadaoCalibParam.m_ROI).copyTo(tempLeftMat);
            m_tempR(m_calib->m_dadaoCalibParam.m_ROI).copyTo(tempRightMat);

            IplImage tempImageLeft = tempLeftMat;
            IplImage tempImageRight = tempRightMat;

            m_dadaoImage[0].m_rectifiedIplImage = cvCloneImage(&tempImageLeft);
            m_dadaoImage[1].m_rectifiedIplImage = cvCloneImage(&tempImageRight);

            //Copy two images to an object.
            //Get their data address first.
            cvGetRawData(m_dadaoImage[0].m_rectifiedIplImage, &dadaoLeftImageData);
            cvGetRawData(m_dadaoImage[1].m_rectifiedIplImage, &dadaoRightImageData);
            //Copy data.
            m_stereo->SetStereoImage(dadaoLeftImageData,  m_dadaoImage[0].m_rectifiedIplImage->width, m_dadaoImage[0].m_rectifiedIplImage->height,
                                     m_dadaoImage[0].m_rectifiedIplImage->widthStep, true,  m_dadaoImage[0].m_capturedTime);
            m_stereo->SetStereoImage(dadaoRightImageData, m_dadaoImage[1].m_rectifiedIplImage->width, m_dadaoImage[1].m_rectifiedIplImage->height,
                                     m_dadaoImage[1].m_rectifiedIplImage->widthStep, false, m_dadaoImage[1].m_capturedTime);

//            sleep(1e6/fps);

            //Save depth image to .pgm
            if( StereoImage::saveDisparity )
                m_stereo->SaveKittiDepthImages( m_dadaoImagePath, i );

            cvReleaseImage(&m_dadaoImage[0].m_rectifiedIplImage);
            cvReleaseImage(&m_dadaoImage[1].m_rectifiedIplImage);
        }
        m_endReading = true;
    }
    //=====================================================================================//
    //=============================ReadKitti===============================================//
    //=====================================================================================//
    //If no dadao calib file, check the kitti calib file.
    else if(m_calib->GetKittiCalibParam(inputDirectory + KITTI_CALIB_PATH))
    {
        m_kittiCalibFilePath = inputDirectory + KITTI_CALIB_PATH;
        m_kittiPoseFilePath = inputDirectory + KITTI_POSE_FILE_PATH;
        m_kittiTimestampsFilePath = inputDirectory + KITTI_TIMESTAMPS_FILE_PATH;
        m_kittiImagePath = inputDirectory;        
         
        if(m_stereo->GetKittiTimestamps(m_kittiTimestampsFilePath))
        {    
            if(m_stereo->GetKittiPoses(m_kittiPoseFilePath))
            {
                //The flag of pose file.
                m_poseFileExist = true;
            }

            m_stereo->m_numOfKittiImage = 10;

            std::cout<<"The image number of dataset is: "<<m_stereo->m_numOfKittiImage<<std::endl;
            m_runningDataset = " / " + QString::number(m_stereo->m_numOfKittiImage) + QString(160,' ') + "Now running Kitti Dataset.";
        }
        else
        {
            return;
        }

        //The speed of reading images.
       // int fps = 10;
        //Temporary address to send data.
        unsigned char* kittiLeftImageData;
        unsigned char* kittiRightImageData;
        //0 = left, 1 = right.
        KittiImage m_kittiImage[2];
        for(int32_t i=0; i<m_stereo->m_numOfKittiImage; ++i)
        {
            //wait reconstruction
             while( StereoImage::loadWaitDisparity ) usleep(1);
            StereoImage::loadWaitDisparity = true;

            //Get left and right image
            m_stereo->GetKittiImages(m_kittiImage, m_kittiImagePath, i);

            //Copy two images to an object.
            //Get their data address first.
            cvGetRawData(m_kittiImage[0].m_image, &kittiLeftImageData);
            cvGetRawData(m_kittiImage[1].m_image, &kittiRightImageData);

            //Copy data.
            m_stereo->SetStereoImage(kittiLeftImageData, m_kittiImage[0].m_image->width, m_kittiImage[0].m_image->height,
                                     m_kittiImage[0].m_image->widthStep, true, m_kittiImage[0].m_capturedTime);
            m_stereo->SetStereoImage(kittiRightImageData, m_kittiImage[1].m_image->width, m_kittiImage[1].m_image->height,
                                     m_kittiImage[1].m_image->widthStep, false, m_kittiImage[1].m_capturedTime);

        //    usleep(1e6/fps);

            //Save depth image to .pgm
            if( StereoImage::saveDisparity )
                m_stereo->SaveKittiDepthImages( m_kittiImagePath, i );

            cvReleaseImage(&m_kittiImage[0].m_image);
            cvReleaseImage(&m_kittiImage[1].m_image);
        }
    }

}
