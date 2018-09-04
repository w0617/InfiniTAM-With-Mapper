#ifndef STEREOIMAGE_H
#define STEREOIMAGE_H

#include <QtCore/QObject>
#include <QtGui/QImage>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

//======================================
#include "include/InfiniTAM.h"
//======================================

#define ELAS_MODE 0
#define SGBM_MODE 1
#define BM_MODE   2
#define SPS_MODE  3

//OpenCV file form to save image
struct DadaoImage
{
    cv::Mat m_rawImage;
    IplImage* m_rectifiedIplImage;
    double m_capturedTime;
};

struct KittiImage
{
    IplImage* m_image;
    double m_capturedTime;
};


class StereoImage : public QObject
{
    Q_OBJECT
public: 

    StereoImage(QObject *parent=0);
    ~StereoImage();


    //Struct to save every couple of stereo image and their parameters.
    struct StereoImageParameters
    {
        // I1, I2 are the input image.
        unsigned char* I1;
        unsigned char* I2;

        // D1, D2 are the disparity map.
        float*         D1;
        float*         D2;

        int            width;
        int            height;
        int            step;
        double         time;

        cv::Mat        m_orbPose;

        /*
         * Default constructor.
         */
        StereoImageParameters ()
        {
            I1           = 0;
            I2           = 0;
            D1           = 0;
            D2           = 0;
            width        = 0;
            height       = 0;
            step         = 0;
            time         = 0;
        }
        /*
         * Copy constructor.
         */
        StereoImageParameters ( StereoImage::StereoImageParameters &src)
        {
            I1 = 0;
            I2 = 0;
            D1 = 0;
            D2 = 0;

            if (src.I1!=0)
            {
                I1 = (unsigned char*)malloc(src.step*src.height*sizeof(unsigned char));
                memcpy(I1, src.I1, src.step*src.height*sizeof(unsigned char));
            }

            if (src.I2!=0)
            {
                I2 = (unsigned char*)malloc(src.step*src.height*sizeof(unsigned char));
                memcpy(I2, src.I2, src.step*src.height*sizeof(unsigned char));
            }

            if (src.D1!=0)
            {
                D1 = (float*)malloc(src.step*src.height*sizeof(float));
                memcpy(D1, src.D1, src.step*src.height*sizeof(float));
            }

            if (src.D2!=0)
            {
                D2 = (float*)malloc(src.step * src.height * sizeof(float));
                memcpy(D2, src.D2, src.step * src.height * sizeof(float));
            }

            width     = src.width;
            height    = src.height;
            step      = src.step;
            time      = src.time;
            m_orbPose = src.m_orbPose;
        }


        ~StereoImageParameters ()
        {
            if (I1!=0) { free(I1); I1 = 0; }
            if (I2!=0) { free(I2); I2 = 0; }
            if (D1!=0) { free(D1); D1 = 0; }
            if (D2!=0) { free(D2); D2 = 0; }
        }
    };

    //Get image timestamp and poses.
    //Dadao timestamps and poses
    bool GetDadaoTimesAndPoses(std::string DadaoCamticsFilePath);

    //Kitti timestamps and poses
    bool GetKittiTimestamps(std::string kittiTimestampsFilePath);
    bool GetKittiPoses(std::string kittiPosesFilePath);

    //Get every left and right image.
    //Dadao dataset
    void GetDadaoImages(DadaoImage m_dadaoImage[2], std::string m_dadaoImagePath, int index);
    //Kitti dataset
    void GetKittiImages(KittiImage m_kittiImage[2], std::string m_kittiImagePath, int index);

    //Save depth image to .pgm
    void SaveKittiDepthImages( std::string m_kittiImagePath, int index );

    //Copy two image to an stereo object.
    void SetStereoImage( unsigned char* imageData, int width, int height, int step, bool cam_left, double captured_time );

    //Set orbslam2 pose matrix
    void SetOrbPose(cv::Mat PoseMatrix){m_stereoImage->m_orbPose = PoseMatrix;}

    //the interface for mainthread to get the stereoimage and send to other thread
    StereoImageParameters* GetCurrStereoImage(){return m_stereoImage;}

    //flag of new images
    void PickUpNewStereo() { m_pickedNewStereo = true; }

    //clear timestamps and poses
    void clear();

    //Vector to save timestamps
    std::vector<double> m_dadaoCapturedTime;
    std::vector<double> m_kittiCapturedTime;

    //Vector to save poses
    std::vector<std::vector<float>> m_kittiPoses;
    std::vector<std::vector<float>> m_dadaoPoses;

    int m_numOfDadaoImage;
    int m_numOfKittiImage;

    int m_frameindex;

    QImage m_displayLeftImage;
    //QImage m_displayRightImage;

    static StereoImageParameters* m_currentFrame ;
    static double cameraFocus;
    static double cameraBaseline;

    static bool loadWaitDisparity;
    static bool saveDisparity;
    static bool showDisparityImage;
    static char computeDisparityMode;

    static bool useInfiniTAM;
    static bool infinitamWaitDisparity;

private:

    //Struct to save every single left and right image.
    struct SingleImage
    {
        unsigned char* data;
        int            width;
        int            height;
        int            step;
        double         time;

        /*
         * Default constructor.
         */
        SingleImage ()
        {
            data         = 0;
            width        = 0;
            height       = 0;
            time         = 0;
        }

        /*
         * Destructor.
         */
        ~SingleImage ()
        {
            if (data!=0)
            {
                free(data); data = 0;
            }
        }
    };


    StereoImageParameters* m_stereoImage;
    SingleImage*  m_leftImage;
    SingleImage*  m_rightImage;

    bool m_pickedNewStereo;

signals:

    void DetectNewStereoImage();

public slots:
};

#endif // STEREOIMAGE_H
