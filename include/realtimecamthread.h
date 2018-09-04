#ifndef REALTIMECAMTHREAD_H
#define REALTIMECAMTHREAD_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtGui/QImage>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <sys/time.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "include/stereoimage.h"
#include "include/loitorusbcam.h"
#include "include/loitorimu.h"
// #include "include/System.h"

const static std::string LOITOR_CAMERA_SETTING_PATH = "/Loitor_VISensor_Setups.txt";
const static std::string LOITOR_CALIB_FILE_PATH = "/StereoCalib.yml";

class RealTimeCamThread : public QThread
{
    Q_OBJECT
public:

    RealTimeCamThread(StereoImage *stereo, QObject *parent = 0);
    ~RealTimeCamThread();

    struct LoitorCalibParam
    {
        cv::Mat m_P1;
        cv::Mat m_P2;
        cv::Mat m_Left_Mapping_1;
        cv::Mat m_Left_Mapping_2;
        cv::Mat m_Right_Mapping_1;
        cv::Mat m_Right_Mapping_2;

        double m_f; // x focal length in pixels.
        double m_cu; // principal point (u-coordinate) in pixels
        double m_cv; // principal point (v-coordinate) in pixels
        double m_baseline;// baseline in meters
    };
    LoitorCalibParam m_loitorCalibParam;

    bool SetInputDirectory(QString inputDirectory);
    bool GetLoitorCalibParam( std::string pathOfLoitorCalibFile );
    void PickedUpNewCamImage() { m_pickedNewCamImage = true; }
    void SetRemapFlag() {m_remapFlag = true;}
    void SetReconstructionFlag() {m_reconstructionFlag = true;}
    void StopRealTimeRecon() {m_reconstructionFlag = false;}
    bool CheckRemapFlagStatus() {return m_remapFlag;}
    bool CheckCalibFlagStatus() {return m_calibFlag;}
    void CloseCamera() { close_img_viewer = true; }
//     void GetORBSLAM(ORB_SLAM2::System *slam){m_slam=slam;}

    bool close_img_viewer;
    bool visensor_Close_IMU_viewer;

    // 当前左右图像的时间戳
    timeval left_stamp,right_stamp;

    QImage m_displayLeftImage;
    QImage m_displayRightImage;
    QImage m_remapLeftImage;
    QImage m_remapRightImage;

    std::string m_fileDirectory;

protected:

    void run();

private:

    StereoImage *m_stereo;
//     ORB_SLAM2::System *m_slam;

    bool m_pickedNewCamImage;
    bool m_remapFlag;
    bool m_calibFlag;
    bool m_reconstructionFlag;

signals:

    void DetectNewCamImage();

public slots:
};

#endif // REALTIMECAMTHREAD_H
