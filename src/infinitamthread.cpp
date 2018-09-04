#include "include/infinitamthread.h"


InfiniTAMThread::InfiniTAMThread(QObject *parent)
    : QThread(parent)
{

}

InfiniTAMThread::~InfiniTAMThread()
{
    UIEngine::Instance()->Shutdown();

    delete mainEngine;
    delete internalSettings;
    delete imageSource;
}

void InfiniTAMThread::InitInfiniTAM(std::string inputDirectory )
{
    std::string posePath  = inputDirectory + INFINITAM_POSE_PATH;
    std::string calibPath = inputDirectory + INFINITAM_CALIB_PATH;
    std::string imagePath = inputDirectory + INFINITAM_IMAGE_PATH;
    std::string dispPath  = inputDirectory + INFINITAM_DISPARITY_PATH;
    
    imageSource = new ImageFileReader( calibPath.data(), imagePath.data(), dispPath.data() );
    if (imageSource == NULL)  return; 
    if (imageSource->calib.disparityCalib.params == Vector2f(0.0f, 0.0f))
    {
        imageSource->calib.disparityCalib.type = ITMDisparityCalib::TRAFO_AFFINE;
        imageSource->calib.disparityCalib.params = Vector2f(1.0f/1000.0f, 0.0f);
    }
    internalSettings = new ITMLibSettings();
    internalSettings->groundTruthPoseFpath = posePath;

    mainEngine = new ITMMainEngine( internalSettings, &imageSource->calib, imageSource->getRGBImageSize() );
    UIEngine::Instance()->Initialise( imageSource, mainEngine, internalSettings->deviceType );
}


void InfiniTAMThread::run()
{
    UIEngine::Instance()->Run();
}
