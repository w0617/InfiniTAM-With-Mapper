#ifndef INFINITAMTHREAD_H
#define INFINITAMTHREAD_H

#include <QtCore/QThread>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>

#include "include/stereoimage.h"
#include "InfiniTAM/Engine/UIEngine.h"

//kitti dataset
const static std::string INFINITAM_POSE_PATH  = "/poses.txt";
const static std::string INFINITAM_CALIB_PATH = "/calib.txt";
const static std::string INFINITAM_IMAGE_PATH = "/image_2/%06i.png";
const static std::string INFINITAM_DISPARITY_PATH = "/Disp-Net/%06i.pfm";

class InfiniTAMThread : public QThread
{
    Q_OBJECT
public:

    InfiniTAMThread( QObject *parent = 0);
    ~InfiniTAMThread();
    
    void InitInfiniTAM(std::string inputDirectory );

protected:

    void run();

};

#endif
