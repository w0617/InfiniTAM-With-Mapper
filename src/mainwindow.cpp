#include "include/mainwindow.h"
#include "include/ui_mainwindow.h"
#include <math.h>

//constructer: initialize all pointers.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{     
    this->ui->setupUi(this);

    m_calib = new CalibrationParameters();
    m_stereo = new StereoImage();
    m_readLocalFileThread = new ReadLocalFileThread(m_calib,m_stereo);
    m_getPoseThread = new GetCameraPoseThread(m_calib,m_stereo);
    m_3dReconstructionThread = new ReconstructionThread(m_calib,m_stereo);
    m_realTimeCamThread = new RealTimeCamThread(m_stereo);
    
    //Init the InfiniTAM thread
    if( StereoImage::useInfiniTAM )
        m_infinitamtThread = new InfiniTAMThread();
    
    m_readingLocalFileFlag = false;
    m_runningRealTimeModeFlag = false;

    QObject::connect(m_stereo,SIGNAL(DetectNewStereoImage()),this,SLOT(DetectNewStereoImage()));
    QObject::connect(m_calib,SIGNAL(DetectNewCalibParam()),this,SLOT(DetectNewCalibParam()));
    QObject::connect(m_realTimeCamThread,SIGNAL(DetectNewCamImage()),this,SLOT(DetectNewCamImage()));

    this->setUp();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_calib;
    delete m_stereo;
    delete m_readLocalFileThread;
    delete m_getPoseThread;
    delete m_3dReconstructionThread;
    delete m_realTimeCamThread;
}

void MainWindow::on_BackgroundCheckBox_clicked()
{
    this->ui->Model3D->SetBackgroundFlag(this->ui->BackgroundCheckBox->isChecked());
}

void MainWindow::on_ShowCameraCheckBox_clicked()
{
    this->ui->Model3D->SetShowCamerasFlag(this->ui->ShowCameraCheckBox->isChecked());
}

void MainWindow::on_FollowCameraCheckBox_clicked()
{
    this->ui->Model3D->SetFollowCameraFlag(this->ui->FollowCameraCheckBox->isChecked());
}

void MainWindow::on_AddPoseButton_clicked()
{
    this->ui->Model3D->AddPose();
}

void MainWindow::on_DeletePoseButton_clicked()
{
    this->ui->Model3D->DelPose();
}

void MainWindow::on_ShowPosesButton_clicked()
{
    this->ui->Model3D->PlayPoses(false);
}

void MainWindow::on_SaveVideoButton_clicked()
{
    this->ui->Model3D->PlayPoses(true);
}

void MainWindow::on_LocalImageModeButton_clicked()
{
    if(m_runningRealTimeModeFlag)
    {
        std::cout<<"Please stop other mode first."<<std::endl;
        return;
    }
    if (m_readingLocalFileFlag)
    {
        // set button text
        this->ui->LocalImageModeButton->setText("LocalImageMode");

        std::cout<<"Stop mapping."<<std::endl;

        // stop stereo scanning
        m_readingLocalFileFlag = false;

        // terminate all processes
        m_readLocalFileThread->terminate();
        m_getPoseThread->terminate();
//        m_3dReconstructionThread->terminate();
        while (m_readLocalFileThread->isRunning()||m_getPoseThread->isRunning()/*||m_3dReconstructionThread->isRunning()*/);

    // starting ...
    }
    else
    {
        // set button text
        this->ui->LocalImageModeButton->setText("Stop");
        std::cout<<"Begin to read local file, please choose a dataset directory."<<std::endl;

        std::cout<<"TODO:Fix the existing memory problem, something does not be released when the program running."<<std::endl;

        // reset everything
        this->ui->Model3D->clearAll();
        this->ui->Model3D->ResetView();

        // start reading from files
        if (m_readLocalFileThread->isRunning())
        {
            m_readLocalFileThread->terminate();
        }

        QString inputDirectroy = QFileDialog::getExistingDirectory (this, tr("Choose Dataset Directory"), "../", QFileDialog::ShowDirsOnly);

        if(m_readLocalFileThread->SetInputDirectory(inputDirectroy))
        {
            m_readLocalFileThread->start();
            
            // start stereo scanning
            m_readingLocalFileFlag = true;
        }
        else
        {
            this->ui->LocalImageModeButton->setText("LocalImageMode");
        }
        
        //=================InfiniTAM===============//
        if(StereoImage::useInfiniTAM)
            m_infinitamtThread->InitInfiniTAM(inputDirectroy.toStdString());
    }
}

void MainWindow::on_RealTimeModeButton_clicked()
{
//    if(m_readingLocalFileFlag)
//    {
//        std::cout<<"Please stop other mode first."<<std::endl;
//        return;
//    }
//    if (m_runningRealTimeModeFlag)
//    {
//        m_realTimeCamThread->StopRealTimeRecon();
//        m_runningRealTimeModeFlag = false;
//        m_getPoseThread->terminate();
//        m_3dReconstructionThread->terminate();
//        while (m_getPoseThread->isRunning()||m_3dReconstructionThread->isRunning());
//    }
//    else
//    {
//        this->ui->tabWidget->setCurrentIndex(1);
//        //TODO: fix this problem
//        std::cout<< "Have to use RealTimeMode without using other mode first." << std::endl;

//        // set button text
//        this->ui->RealTimeModeButton->setText("Stop");
//        std::cout<<"Begin the real time mode, please choose the setting directory."<<std::endl;
//        std::cout<<"TODO:Fix the existing memory problem, something does not be released when the program running."<<std::endl;

//        //QString settingDirectory = QFileDialog::getExistingDirectory (this, tr("Choose camera setting Directory"), "../", QFileDialog::ShowDirsOnly);
//        /*
//        if(m_realTimeCamThread->SetInputDirectory(settingDirectory))
//        {
//            //have to start getting camera images first, if get calib params before getting camera images, the mapper will crash
//            m_realTimeCamThread->start();
//            m_runningRealTimeModeFlag = true;
//        }
//        else
//        {
//            std::cout<<"Can not get the right directory."<<std::endl;
//            this->ui->RealTimeModeButton->setText("RealTimeMode");
//        }
//        */

//        //have to start getting camera images first, if get calib params before getting camera images, the mapper will crash
//        m_realTimeCamThread->start();
//        m_runningRealTimeModeFlag = true;
//    }
}

void MainWindow::on_ResetViewButton_clicked()
{
    this->ui->Model3D->ResetView();
}

void MainWindow::on_RecordCheckBox_clicked()
{
    //this->ui->Model3D->createNewRecordDirectory();
    this->ui->Model3D->SetRecordFlag(this->ui->RecordCheckBox->isChecked());
}

void MainWindow::on_ExitButton_clicked()
{
    std::cout<< "Exit mapper " << std::endl;
    if(StereoImage::useInfiniTAM)
        delete m_infinitamtThread;
    exit(0);
}

void MainWindow::DetectNewCalibParam()
{
    m_stereo->clear();

    if( m_getPoseThread->isRunning() )
    {
        m_getPoseThread->quit();
        while( m_getPoseThread->isRunning() );
    }

    QObject::disconnect(m_getPoseThread,SIGNAL(DetectNewCameraPose()),this,SLOT(DetectNewCameraPose()));
    delete m_getPoseThread;
    m_getPoseThread = 0;

    if( m_3dReconstructionThread->isRunning() )
    {
        m_3dReconstructionThread->quit();
        while( m_3dReconstructionThread->isRunning() );
    }

    QObject::disconnect(m_3dReconstructionThread,SIGNAL(DetectNewMap()),this,SLOT(DetectNewMap()));
    delete m_3dReconstructionThread;
    m_3dReconstructionThread = 0;

    m_getPoseThread = new GetCameraPoseThread(m_calib,m_stereo);
    m_3dReconstructionThread = new ReconstructionThread(m_calib,m_stereo);

    // connect to the objects for communication.
    QObject::connect(m_getPoseThread,SIGNAL(DetectNewCameraPose()),this,SLOT(DetectNewCameraPose()));
    QObject::connect(m_3dReconstructionThread,SIGNAL(DetectNewMap()),this,SLOT(DetectNewMap()));

    m_calib->PickedUpNewCalibParam();
}

void MainWindow::DetectNewStereoImage()
{        
    if (m_readingLocalFileFlag)
    {
        //Show the current left image
        QImage newImg = m_stereo->m_displayLeftImage.scaled(this->ui->LeftImageLabel->width(), this->ui->LeftImageLabel->height());
        this->ui->LeftImageLabel->setPixmap(QPixmap::fromImage(newImg));

        //Show the status bar message
        //TODO: let the statusbar show more information
        QString msg = "The number of reading frame is:   " + QString::number(m_stereo->m_frameindex+1, 10) + m_readLocalFileThread->m_runningDataset;
        this->ui->statusBar->showMessage(msg);

    }
    else if (m_runningRealTimeModeFlag)
    {
        QImage rawImgL = m_realTimeCamThread->m_displayLeftImage.scaled(this->ui->LeftImageLabel->width(),this->ui->LeftImageLabel->height());
        this->ui->LeftImageLabel->setPixmap(QPixmap::fromImage(rawImgL));

        QString msg = "Now running real time mode.";
        this->ui->statusBar->showMessage(msg);
    }

    //Get the current stereo image
    StereoImage::StereoImageParameters stereoImg(*m_stereo->GetCurrStereoImage());

    //flag to read next stereo image
    m_stereo->PickUpNewStereo();

    //make sure the thread finished the last action
    if ((m_readingLocalFileFlag || m_runningRealTimeModeFlag) && !m_getPoseThread->isRunning())
    {
        //send image pointer and the pose file status to the POSE(VO) thread
        m_getPoseThread->SendImage(stereoImg, m_readLocalFileThread->CheckPoseFileStatus());
        m_getPoseThread->start();
    }
}

void MainWindow::DetectNewCameraPose()
{
    //get image and pose from the VO thread
    StereoImage::StereoImageParameters stereoImgWithPose(*m_getPoseThread->GetStereoImage());
    libviso2_Matrix Homographytotal = m_getPoseThread->GetHomographyTotal();
    m_getPoseThread->PickUpNewCamPose();

    //make sure the thread finished the last action
    if ((m_readingLocalFileFlag || m_runningRealTimeModeFlag) && !m_3dReconstructionThread->isRunning())
    {
        m_3dReconstructionThread->SendImageAndPose(stereoImgWithPose, Homographytotal);
        m_3dReconstructionThread->start();
    }
}

void MainWindow::DetectNewMap()
{
    if( StereoImage::showDisparityImage ) this->ShowDepthImage();

  //  if(this->ui->tabWidget->currentIndex()==0)
    {
        this->ui->Model3D->AddCamera(m_3dReconstructionThread->GetHomographyTotal(),0.1);
        this->ui->Model3D->AddPoints(m_3dReconstructionThread->GetMapPoints());
        this->ui->Model3D->FollowCamera(m_3dReconstructionThread->GetHomographyTotal());
    }

    m_3dReconstructionThread->PickupNewMap();

    if(m_readLocalFileThread->CheckReadingStatus()&&this->ui->RecordCheckBox->isChecked())
        this->ui->Model3D->ShowMap();
    
        //===========================InfiniTAM============================//
    if( StereoImage::useInfiniTAM )
        if(!m_infinitamtThread->isRunning()) m_infinitamtThread->start();
}

void MainWindow::DetectNewCamImage()
{
    if(this->ui->tabWidget->currentIndex()==1)
    {

    }

    m_realTimeCamThread->PickedUpNewCamImage();
}

void MainWindow::on_DisparityModeBox_activated(const QString &arg1)
{
    if( arg1 == "     BM-Mode" )
    {
        StereoImage::computeDisparityMode = BM_MODE;
        cout<<"BM_MODE to compute disparity."<<endl;
        this->slot_reset();
    }
    if( arg1 == "    SGBM-Mode" )
    {
        StereoImage::computeDisparityMode = SGBM_MODE;
        cout<<"SGBM_MODE to compute disparity."<<endl;
        this->slot_reset();
    }
    if( arg1 == "     Elas-Mode" )
    {
        StereoImage::computeDisparityMode = ELAS_MODE;
        cout<<"ELAS_MODE to compute disparity."<<endl;
        this->slot_reset();
    }
    if( arg1 == "     SPS-Mode" )
    {
        StereoImage::computeDisparityMode = SPS_MODE;
        cout<<"SPS_MODE to compute disparity."<<endl;
        this->slot_reset();
    }
}


//============================    SGBM   =========================================//

void MainWindow::slot_slider_NumberOfDisparitiesSG(int value)
{
    this->on_Slider_NumberOfDisparitiesSG_sliderReleased();
}

void MainWindow::slot_slider_SADWindowSizeSG(int value)
{
    this->on_Slider_SADWindowSizeSG_sliderReleased();
}

void MainWindow::slot_slider_MinDisparitySG(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_MinDisparitySG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetMinDisparity(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_UniquenessRatioSG(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_UniquenessRatioSG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetUniquenessRatio(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_SpeckleWindowSizeSG(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_SpeckleWindowSizeSG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSpeckleWindowSize(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_SpeckleRangeSG(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_SpeckleRangeSG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSpeckleRange(value);

    if (this->autoUpdateEnabled)
        this->update();
}


//==============================   BM   =========================================//

void MainWindow::slot_slider_PreFilterSize(int value)
{
    this->on_Slider_PreFilterSize_sliderReleased();
}

void MainWindow::slot_slider_SADWindowSize(int value)
{
    this->on_Slider_SADWindowSize_sliderReleased();
}

void MainWindow::slot_slider_NumberOfDisparities(int value)
{
    this->on_Slider_NumberOfDisparities_sliderReleased();
}

void MainWindow::slot_slider_PreFilterCap(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_PreFilterCap->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetPreFilterCap(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_MinDisparity(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_MinDisparity->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetMinDisparity(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_TextureThreshold(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_TextureThreshold->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetTextureThreshold(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_UniquenessRatio(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_UniquenessRatio->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetUniquenessRatio(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_SpeckleWindowSize(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_SpeckleWindowSize->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetSpeckleWindowSize(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::slot_slider_SpeckleRange(int value)
{
    stringstream valueString;

    valueString << value;
    this->ui->label_SpeckleRange->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetSpeckleRange(value);

    if (this->autoUpdateEnabled)
        this->update();
}

//===================================   Release   ====================================//

void MainWindow::on_Slider_NumberOfDisparities_sliderReleased()
{
    stringstream valueString;
    int value = this->ui->Slider_NumberOfDisparities->value();
    int raster = value % 16;

    if (raster > (value / 2))
        raster = (value % 16) - raster;
    else
        raster = raster * -1;

    value = value + raster;

    this->ui->Slider_NumberOfDisparities->setSliderPosition(value);

    valueString << value;
    this->ui->label_NumberOfDisparities->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetNumberOfDisparities(value);

    if (((value % 16) == 0) && this->autoUpdateEnabled)
        this->update();
}

void MainWindow::on_Slider_PreFilterSize_sliderReleased()
{
    stringstream valueString;
    int value = this->ui->Slider_PreFilterSize->value();

    if (!(value % 2))
        value -= 1;

    this->ui->Slider_PreFilterSize->setSliderPosition(value);

    valueString << value;
    this->ui->label_PreFilterSize->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetPreFilterSize(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::on_Slider_SADWindowSize_sliderReleased()
{
    stringstream valueString;
    int value = this->ui->Slider_SADWindowSize->value();

    if (!(value % 2))
        value -= 1;

    this->ui->Slider_SADWindowSize->setSliderPosition(value);

    valueString << value;
    this->ui->label_SADWindowSize->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->bm.SetSADWindowSize(value);

    if (this->autoUpdateEnabled)
        this->update();
}

void MainWindow::on_Slider_NumberOfDisparitiesSG_sliderReleased()
{
    stringstream valueString;
    int value = this->ui->Slider_NumberOfDisparitiesSG->value();
    int raster = value % 16;

    if (raster > (value / 2))
        raster = (value % 16) - raster;
    else
        raster = raster * -1;

    value = value + raster;

    this->ui->Slider_NumberOfDisparitiesSG->setSliderPosition(value);

    valueString << value;
    this->ui->label_NumberOfDisparitiesSG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetNumberOfDisparities(value);

    if (((value % 16) == 0) && this->autoUpdateEnabled)
        this->update();
}

void MainWindow::on_Slider_SADWindowSizeSG_sliderReleased()
{
    stringstream valueString;
    int value = this->ui->Slider_SADWindowSizeSG->value();

    if (!(value % 2))
        value -= 1;

    this->ui->Slider_SADWindowSizeSG->setSliderPosition(value);

    valueString << value;
    this->ui->label_SADWindowSizeSG->setText(valueString.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSADWindowSize(value);

    if (this->autoUpdateEnabled)
        this->update();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//set slider and algorithm parameters.
void MainWindow::setUp()
{    
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::green);
    this->ui->label_1->setPalette(pa);
    this->ui->label_2->setPalette(pa);
    this->ui->label_3->setPalette(pa);
    // ELAS BM SGBM depth image label (dont know why cant change label name TAT)

    stringstream value;

    this->autoUpdateEnabled = this->ui->cb_auto_update->isChecked();

    value << this->ui->Slider_MinDisparity->value();
    this->ui->label_MinDisparity->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetMinDisparity(this->ui->Slider_MinDisparity->value());
    value.str("");

    value << this->ui->Slider_NumberOfDisparities->value();
    this->ui->label_NumberOfDisparities->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetNumberOfDisparities(this->ui->Slider_NumberOfDisparities->value());
    value.str("");

    value << this->ui->Slider_PreFilterCap->value();
    this->ui->label_PreFilterCap->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetPreFilterCap(this->ui->Slider_PreFilterCap->value());
    value.str("");

    value << this->ui->Slider_PreFilterSize->value();
    this->ui->label_PreFilterSize->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetPreFilterSize(this->ui->Slider_PreFilterSize->value());
    value.str("");

    value << this->ui->Slider_SADWindowSize->value();
    this->ui->label_SADWindowSize->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetSADWindowSize(this->ui->Slider_SADWindowSize->value());
    value.str("");

    value << this->ui->Slider_SpeckleRange->value();
    this->ui->label_SpeckleRange->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetSpeckleRange(this->ui->Slider_SpeckleRange->value());
    value.str("");

    value << this->ui->Slider_SpeckleWindowSize->value();
    this->ui->label_SpeckleWindowSize->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetSpeckleWindowSize(this->ui->Slider_SpeckleWindowSize->value());
    value.str("");

    value << this->ui->Slider_TextureThreshold->value();
    this->ui->label_TextureThreshold->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetTextureThreshold(this->ui->Slider_TextureThreshold->value());
    value.str("");

    value << this->ui->Slider_UniquenessRatio->value();
    this->ui->label_UniquenessRatio->setText(value.str().c_str());
    this->m_3dReconstructionThread->bm.SetUniquenessRatio(this->ui->Slider_UniquenessRatio->value());
    value.str("");

    value << this->ui->Slider_MinDisparitySG->value();
    this->ui->label_MinDisparitySG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetMinDisparity(this->ui->Slider_MinDisparitySG->value());
    value.str("");

    value << this->ui->Slider_NumberOfDisparitiesSG->value();
    this->ui->label_NumberOfDisparitiesSG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetNumberOfDisparities(this->ui->Slider_NumberOfDisparitiesSG->value());
    value.str("");

    value << this->ui->Slider_UniquenessRatioSG->value();
    this->ui->label_UniquenessRatioSG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetUniquenessRatio(this->ui->Slider_UniquenessRatioSG->value());
    value.str("");

    value << this->ui->Slider_SpeckleWindowSizeSG->value();
    this->ui->label_SpeckleWindowSizeSG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSpeckleWindowSize(this->ui->Slider_SpeckleWindowSizeSG->value());
    value.str("");

    value << this->ui->Slider_SpeckleRangeSG->value();
    this->ui->label_SpeckleRangeSG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSpeckleRange(this->ui->Slider_SpeckleRangeSG->value());
    value.str("");

    value << this->ui->Slider_SADWindowSizeSG->value();
    this->ui->label_SADWindowSizeSG->setText(value.str().c_str());
    this->m_3dReconstructionThread->sgbm.SetSADWindowSize(this->ui->Slider_SADWindowSizeSG->value());
    value.str("");
}

void MainWindow::slot_reset()
{
    bool autoUpChecked = this->ui->cb_auto_update->isChecked();

    if (autoUpChecked)
        this->ui->cb_auto_update->setChecked(false);

    if( StereoImage::computeDisparityMode == BM_MODE )
    {
        this->slot_slider_PreFilterCap(31);
        this->ui->Slider_PreFilterCap->setValue(31);
        this->slot_slider_PreFilterSize(5);
        this->ui->Slider_PreFilterSize->setValue(5);
        this->slot_slider_SADWindowSize(9);
        this->ui->Slider_SADWindowSize->setValue(9);
        this->slot_slider_MinDisparity(0);
        this->ui->Slider_MinDisparity->setValue(0);
        this->slot_slider_NumberOfDisparities(48);
        this->ui->Slider_NumberOfDisparities->setValue(48);
        this->slot_slider_TextureThreshold(10);
        this->ui->Slider_TextureThreshold->setValue(10);
        this->slot_slider_UniquenessRatio(15);
        this->ui->Slider_UniquenessRatio->setValue(15);
        this->slot_slider_SpeckleWindowSize(100);
        this->ui->Slider_SpeckleWindowSize->setValue(100);
        this->slot_slider_SpeckleRange(32);
        this->ui->Slider_SpeckleRange->setValue(32);
    }

    if( StereoImage::computeDisparityMode == SGBM_MODE )
    {
        this->slot_slider_MinDisparitySG(0);
        this->ui->Slider_MinDisparitySG->setValue(0);
        this->slot_slider_NumberOfDisparitiesSG(48);
        this->ui->Slider_NumberOfDisparitiesSG->setValue(48);
        this->slot_slider_UniquenessRatioSG(15);
        this->ui->Slider_UniquenessRatioSG->setValue(15);
        this->slot_slider_SpeckleWindowSizeSG(100);
        this->ui->Slider_SpeckleWindowSizeSG->setValue(100);
        this->slot_slider_SpeckleRangeSG(32);
        this->ui->Slider_SpeckleRangeSG->setValue(32);
        this->slot_slider_SADWindowSizeSG(9);
        this->ui->Slider_SADWindowSizeSG->setValue(9);
    }

    if (autoUpChecked)
    {    this->ui->cb_auto_update->setChecked(true); this->update(); }
}

void MainWindow::slot_auto_update()
{
    if (this->ui->cb_auto_update->isChecked())
    {
        this->autoUpdateEnabled = true;
        cout << "Now depth image can follow parameter change." << endl;
    }
    else
        this->autoUpdateEnabled = false;
}

void MainWindow::update()
{
    Mat leftImage(StereoImage::m_currentFrame->height, StereoImage::m_currentFrame->step, CV_8U);
    Mat rightImage(StereoImage::m_currentFrame->height, StereoImage::m_currentFrame->step, CV_8U);

    if( !m_readingLocalFileFlag )
    {
        this->m_3dReconstructionThread->bm_arrayToMat(StereoImage::m_currentFrame->I1, leftImage);
        this->m_3dReconstructionThread->bm_arrayToMat(StereoImage::m_currentFrame->I2, rightImage);

        if( StereoImage::computeDisparityMode == BM_MODE )
        {
            this->m_3dReconstructionThread->bm.setImages(leftImage, rightImage);
            this->m_3dReconstructionThread->bm_matToArray(m_3dReconstructionThread->bm.updateBM(), StereoImage::m_currentFrame->D1);
        }

        if( StereoImage::computeDisparityMode == SGBM_MODE )
        {
            this->m_3dReconstructionThread->sgbm.setImages(leftImage, rightImage);
            this->m_3dReconstructionThread->bm_matToArray(m_3dReconstructionThread->sgbm.updateSGBM(), StereoImage::m_currentFrame->D1);
        }
    }

    this->ShowDepthImage();
}

//============================   Show Depth Image   ===================================//

void MainWindow::on_tabWidget_currentChanged (int index)
{
    if( index == 1 )
        //compute and show depth image
        StereoImage::showDisparityImage = true;
    else
        StereoImage::showDisparityImage = false;
}

void MainWindow::ShowDepthImage()
{
    cv::Mat depthImage(StereoImage::m_currentFrame->height, StereoImage::m_currentFrame->width, CV_8U);
    float *address;
    float temp;
    address = StereoImage::m_currentFrame->D1;

    for(int i=0; i<depthImage.rows; i++)
    {
        for(int j=0; j<depthImage.cols; j++)
        {
            temp = ( StereoImage::cameraFocus*StereoImage::cameraBaseline/(*address) ) + 38;
            if(temp<0)   temp = 0;
            if(temp>255) temp = 255;
            depthImage.at<uchar>(i,j) = ceil(temp);
            address ++;
        }
    }

  //  cout<< "focus: "<< StereoImage::cameraFocus<< "    baseline: "<<StereoImage::cameraBaseline<<endl;

    cv::Mat showImage;
    cv::cvtColor(depthImage, showImage, CV_GRAY2RGB);
    QImage image = QImage((uchar*) showImage.data, showImage.cols, showImage.rows, showImage.step, QImage::Format_RGB888);
    image.scaled( this->ui->ElasDepthImage->width(), this->ui->ElasDepthImage->height() ); //How to cut the black edge

    if( StereoImage::computeDisparityMode == ELAS_MODE )
    {
        this->ui->label_1->setText(QApplication::translate("MainWindow", "ELAS", 0, QApplication::UnicodeUTF8));
        this->ui->ElasDepthImage->setPixmap( QPixmap::fromImage(image) );
    }

    if( StereoImage::computeDisparityMode == SGBM_MODE )
    {
        this->ui->label_2->setText(QApplication::translate("MainWindow", "SGBM", 0, QApplication::UnicodeUTF8));
        this->ui->SGBMDepthImage->setPixmap( QPixmap::fromImage(image) );
    }

    if( StereoImage::computeDisparityMode == BM_MODE )
    {
        this->ui->label_3->setText(QApplication::translate("MainWindow", "BM", 0, QApplication::UnicodeUTF8));
        this->ui->BMDepthImage->setPixmap( QPixmap::fromImage(image) );
    }

    if( StereoImage::computeDisparityMode == SPS_MODE )
    {
        this->ui->label_3->setText(QApplication::translate("MainWindow", "SPS", 0, QApplication::UnicodeUTF8));
        this->ui->BMDepthImage->setPixmap( QPixmap::fromImage(image) );
    }
}
