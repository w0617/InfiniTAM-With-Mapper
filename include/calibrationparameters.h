#ifndef CALIBRATIONPARAMETERS_H
#define CALIBRATIONPARAMETERS_H

#include <QtCore/QObject>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <array>
#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "include/stereoimage.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

class CalibrationParameters : public QObject
{
    Q_OBJECT

public:

    CalibrationParameters( QObject* a_parent=0 );
    ~CalibrationParameters();

    //The flag to check what kind of calib exist to decide using what params.
    enum DatasetTypeFlag
    {
        DADAO_DATASET_FLAG = 0,
        KITTI_DATASET_FLAG,
        LOITOR_DATASET_FLAG,
        OTHER_DATASET_FLAG
    };

    //dadao dataset, opencv calibration parameters.
    struct DadaoCalibParam
    {
        std::string m_calib_time;
        int m_ImageHeight;
        int m_ImageWidth;
        cv::Mat m_CM1;
        cv::Mat m_CM2;
        cv::Mat m_D1;
        cv::Mat m_D2;
        cv::Mat m_R;
        cv::Mat m_T;
        cv::Mat m_E;
        cv::Mat m_F;
        cv::Mat m_R1;
        cv::Mat m_R2;
        cv::Mat m_P1;
        cv::Mat m_P2;
        cv::Mat m_Q;
        cv::Rect m_ROI;
        cv::Mat m_Left_Mapping_1;
        cv::Mat m_Left_Mapping_2;
        cv::Mat m_Right_Mapping_1;
        cv::Mat m_Right_Mapping_2;

        double m_f; // x focal length in pixels.
        double m_cu; // principal point (u-coordinate) in pixels
        double m_cv; // principal point (v-coordinate) in pixels
        double m_baseline;// baseline in meters
    };
    DadaoCalibParam m_dadaoCalibParam;

    //kitti dataset, calibration parameters
    struct KittiCalibParam
    {
        double m_f; // x focal length in pixels.
        double m_cu; // principal point (u-coordinate) in pixels
        double m_cv; // principal point (v-coordinate) in pixels
        double m_baseline;// baseline in meters
    };
    KittiCalibParam m_KittiCalibParam;

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

    //get dadao dataset opencv calibration parameters.
    bool GetDadaoCalibParam( std::string pathOfDadaoCalibFile );

    //get kitti dataset calibration parameters.
    bool GetKittiCalibParam( std::string pathOfKittiCalibFile );

    //get loitor dataset calib params
    bool GetLoitorCalibParam( std::string pathOfLoitorCalibFile );

    //get the running data type
    int CheckRunDataType(){return m_runningDataType;}

    void PickedUpNewCalibParam() { m_pickedNewCalibParam = true; }

private:

    int m_runningDataType;
    bool m_pickedNewCalibParam;

signals:

    void DetectNewCalibParam();

public slots:
};

#endif // CALIBRATIONPARAMETERS_H
