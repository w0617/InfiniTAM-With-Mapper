#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QDialog>
#include <QtCore/QMutex>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <sys/time.h>
#include <opencv/highgui.h>

#include "include/calibrationparameters.h"
#include "include/stereoimage.h"
#include "include/readlocalfilethread.h"
#include "include/reconstructionthread.h"
#include "include/modelpainting.h"
#include "include/getcameraposethread.h"
#include "include/realtimecamthread.h"
#include "include/infinitamthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:

    //slider of bm and sgbm
    void slot_slider_MinDisparitySG(int value);
    void slot_slider_NumberOfDisparitiesSG(int value);
    void slot_slider_UniquenessRatioSG(int value);
    void slot_slider_SpeckleWindowSizeSG(int value);
    void slot_slider_SpeckleRangeSG(int value);
    void slot_slider_SADWindowSizeSG(int value);
    void slot_slider_PreFilterCap(int value);
    void slot_slider_PreFilterSize(int value);
    void slot_slider_SADWindowSize(int value);
    void slot_slider_MinDisparity(int value);
    void slot_slider_NumberOfDisparities(int value);
    void slot_slider_TextureThreshold(int value);
    void slot_slider_UniquenessRatio(int value);
    void slot_slider_SpeckleWindowSize(int value);
    void slot_slider_SpeckleRange(int value);

    void slot_reset();
    void slot_auto_update();


private:

    Ui::MainWindow *ui;
    CalibrationParameters *m_calib;
    StereoImage *m_stereo;
    ReadLocalFileThread *m_readLocalFileThread;
    GetCameraPoseThread *m_getPoseThread;
    ReconstructionThread *m_3dReconstructionThread;
    RealTimeCamThread *m_realTimeCamThread;
    InfiniTAMThread *m_infinitamtThread;
//     ORB_SLAM2::System *m_slam;


    bool m_readingLocalFileFlag;
    bool m_runningRealTimeModeFlag;

    bool autoUpdateEnabled;
    void update(void);
    void setUp(void);
    void ShowDepthImage();

private slots:

    void on_BackgroundCheckBox_clicked();
    void on_ShowCameraCheckBox_clicked();
    void on_FollowCameraCheckBox_clicked();
    void on_AddPoseButton_clicked();
    void on_DeletePoseButton_clicked();
    void on_ShowPosesButton_clicked();
    void on_SaveVideoButton_clicked();
    void on_LocalImageModeButton_clicked();
    void on_RealTimeModeButton_clicked();
    void on_ExitButton_clicked();
    void on_ResetViewButton_clicked();
    void on_RecordCheckBox_clicked();
    void on_DisparityModeBox_activated(const QString &arg1);
    void on_Slider_NumberOfDisparities_sliderReleased();
    void on_Slider_PreFilterSize_sliderReleased();
    void on_Slider_SADWindowSize_sliderReleased();
    void on_Slider_NumberOfDisparitiesSG_sliderReleased();
    void on_Slider_SADWindowSizeSG_sliderReleased();
    void on_tabWidget_currentChanged(int index);

    void DetectNewCalibParam();
    void DetectNewStereoImage();
    void DetectNewCameraPose();
    void DetectNewMap();
    void DetectNewCamImage();

};

#endif // MAINWINDOW_H
