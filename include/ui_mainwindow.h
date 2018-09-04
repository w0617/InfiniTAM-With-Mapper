/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "modelpainting.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    ModelPainting *Model3D;
    QHBoxLayout *horizontalLayout_2;
    QLabel *LeftImageLabel;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *ElasDepthImage;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *SGBMDepthImage;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *BMDepthImage;
    QLabel *label_1;
    QLabel *label_3;
    QLabel *label_2;
    QFrame *line;
    QFrame *line_2;
    QFrame *frame_26;
    QLabel *NumberOfDisparitiesSG;
    QLabel *UniquenessRatioSG;
    QLabel *SpeckleWindowSizeSG;
    QLabel *SpeckleRangeSG;
    QLabel *MinDisparitySG;
    QSlider *Slider_MinDisparitySG;
    QSlider *Slider_NumberOfDisparitiesSG;
    QSlider *Slider_UniquenessRatioSG;
    QSlider *Slider_SpeckleWindowSizeSG;
    QSlider *Slider_SpeckleRangeSG;
    QSlider *Slider_SADWindowSizeSG;
    QLabel *SADWindowSizeSG;
    QLabel *BMParameter_2;
    QLabel *label_NumberOfDisparitiesSG;
    QLabel *label_UniquenessRatioSG;
    QLabel *label_SpeckleWindowSizeSG;
    QLabel *label_MinDisparitySG;
    QLabel *label_SpeckleRangeSG;
    QLabel *label_SADWindowSizeSG;
    QFrame *frame_25;
    QSlider *Slider_PreFilterCap;
    QLabel *PreFilterCap;
    QLabel *SADWindowSize;
    QLabel *NumberOfDisparities;
    QLabel *TextureThreshold;
    QLabel *UniquenessRatio;
    QLabel *SpeckleWindowSize;
    QLabel *SpeckleRange;
    QLabel *PreFilterSize;
    QLabel *MinDisparity;
    QSlider *Slider_PreFilterSize;
    QSlider *Slider_MinDisparity;
    QSlider *Slider_SADWindowSize;
    QSlider *Slider_NumberOfDisparities;
    QSlider *Slider_TextureThreshold;
    QSlider *Slider_UniquenessRatio;
    QSlider *Slider_SpeckleWindowSize;
    QSlider *Slider_SpeckleRange;
    QLabel *BMParameter;
    QLabel *label_MinDisparity;
    QLabel *label_NumberOfDisparities;
    QLabel *label_PreFilterSize;
    QLabel *label_SpeckleRange;
    QLabel *label_SpeckleWindowSize;
    QLabel *label_TextureThreshold;
    QLabel *label_SADWindowSize;
    QLabel *label_PreFilterCap;
    QLabel *label_UniquenessRatio;
    QWidget *verticalLayoutWidget_13;
    QVBoxLayout *verticalLayout_24;
    QPushButton *pb_reset;
    QPushButton *ResetViewButton;
    QPushButton *LocalImageModeButton;
    QPushButton *RealTimeModeButton;
    QPushButton *ExitButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_11;
    QCheckBox *cb_auto_update;
    QCheckBox *BackgroundCheckBox;
    QCheckBox *ShowCameraCheckBox;
    QCheckBox *FollowCameraCheckBox;
    QCheckBox *RecordCheckBox;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_14;
    QComboBox *DisparityModeBox;
    QPushButton *SaveVideoButton;
    QPushButton *ShowPosesButton;
    QPushButton *DeletePoseButton;
    QPushButton *AddPoseButton;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1531, 924);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(800, 0));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 1041, 861));
        tabWidget->setMouseTracking(false);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        verticalLayoutWidget = new QWidget(tab_1);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1041, 831));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 10);
        Model3D = new ModelPainting(verticalLayoutWidget);
        Model3D->setObjectName(QString::fromUtf8("Model3D"));

        horizontalLayout_3->addWidget(Model3D);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        LeftImageLabel = new QLabel(verticalLayoutWidget);
        LeftImageLabel->setObjectName(QString::fromUtf8("LeftImageLabel"));

        horizontalLayout_2->addWidget(LeftImageLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout_2->setStretch(0, 5);
        verticalLayout_2->setStretch(1, 3);

        verticalLayout->addLayout(verticalLayout_2);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(-60, 0, 1101, 271));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        ElasDepthImage = new QLabel(layoutWidget);
        ElasDepthImage->setObjectName(QString::fromUtf8("ElasDepthImage"));

        horizontalLayout_4->addWidget(ElasDepthImage);

        layoutWidget_2 = new QWidget(tab_2);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(-60, 280, 1101, 271));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        SGBMDepthImage = new QLabel(layoutWidget_2);
        SGBMDepthImage->setObjectName(QString::fromUtf8("SGBMDepthImage"));

        horizontalLayout_5->addWidget(SGBMDepthImage);

        layoutWidget_3 = new QWidget(tab_2);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(-60, 560, 1101, 271));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        BMDepthImage = new QLabel(layoutWidget_3);
        BMDepthImage->setObjectName(QString::fromUtf8("BMDepthImage"));

        horizontalLayout_6->addWidget(BMDepthImage);

        label_1 = new QLabel(tab_2);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setGeometry(QRect(990, 240, 41, 31));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1000, 800, 31, 31));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(980, 520, 51, 31));
        line = new QFrame(tab_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(-3, 540, 1051, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(tab_2);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 260, 1041, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(tab_2, QString());
        frame_26 = new QFrame(centralWidget);
        frame_26->setObjectName(QString::fromUtf8("frame_26"));
        frame_26->setEnabled(true);
        frame_26->setGeometry(QRect(1080, 40, 411, 231));
        frame_26->setFrameShape(QFrame::StyledPanel);
        frame_26->setFrameShadow(QFrame::Raised);
        NumberOfDisparitiesSG = new QLabel(frame_26);
        NumberOfDisparitiesSG->setObjectName(QString::fromUtf8("NumberOfDisparitiesSG"));
        NumberOfDisparitiesSG->setGeometry(QRect(20, 70, 161, 31));
        UniquenessRatioSG = new QLabel(frame_26);
        UniquenessRatioSG->setObjectName(QString::fromUtf8("UniquenessRatioSG"));
        UniquenessRatioSG->setGeometry(QRect(20, 100, 131, 31));
        SpeckleWindowSizeSG = new QLabel(frame_26);
        SpeckleWindowSizeSG->setObjectName(QString::fromUtf8("SpeckleWindowSizeSG"));
        SpeckleWindowSizeSG->setGeometry(QRect(20, 130, 171, 31));
        SpeckleRangeSG = new QLabel(frame_26);
        SpeckleRangeSG->setObjectName(QString::fromUtf8("SpeckleRangeSG"));
        SpeckleRangeSG->setGeometry(QRect(20, 160, 111, 31));
        MinDisparitySG = new QLabel(frame_26);
        MinDisparitySG->setObjectName(QString::fromUtf8("MinDisparitySG"));
        MinDisparitySG->setGeometry(QRect(20, 40, 111, 31));
        Slider_MinDisparitySG = new QSlider(frame_26);
        Slider_MinDisparitySG->setObjectName(QString::fromUtf8("Slider_MinDisparitySG"));
        Slider_MinDisparitySG->setGeometry(QRect(180, 40, 171, 31));
        Slider_MinDisparitySG->setMinimum(-100);
        Slider_MinDisparitySG->setMaximum(100);
        Slider_MinDisparitySG->setValue(0);
        Slider_MinDisparitySG->setSliderPosition(0);
        Slider_MinDisparitySG->setOrientation(Qt::Horizontal);
        Slider_NumberOfDisparitiesSG = new QSlider(frame_26);
        Slider_NumberOfDisparitiesSG->setObjectName(QString::fromUtf8("Slider_NumberOfDisparitiesSG"));
        Slider_NumberOfDisparitiesSG->setGeometry(QRect(180, 70, 171, 31));
        Slider_NumberOfDisparitiesSG->setMinimum(16);
        Slider_NumberOfDisparitiesSG->setMaximum(256);
        Slider_NumberOfDisparitiesSG->setSingleStep(16);
        Slider_NumberOfDisparitiesSG->setPageStep(16);
        Slider_NumberOfDisparitiesSG->setValue(48);
        Slider_NumberOfDisparitiesSG->setOrientation(Qt::Horizontal);
        Slider_NumberOfDisparitiesSG->setTickPosition(QSlider::TicksBelow);
        Slider_NumberOfDisparitiesSG->setTickInterval(16);
        Slider_UniquenessRatioSG = new QSlider(frame_26);
        Slider_UniquenessRatioSG->setObjectName(QString::fromUtf8("Slider_UniquenessRatioSG"));
        Slider_UniquenessRatioSG->setGeometry(QRect(180, 100, 171, 31));
        Slider_UniquenessRatioSG->setMaximum(100);
        Slider_UniquenessRatioSG->setValue(15);
        Slider_UniquenessRatioSG->setOrientation(Qt::Horizontal);
        Slider_SpeckleWindowSizeSG = new QSlider(frame_26);
        Slider_SpeckleWindowSizeSG->setObjectName(QString::fromUtf8("Slider_SpeckleWindowSizeSG"));
        Slider_SpeckleWindowSizeSG->setGeometry(QRect(180, 130, 171, 31));
        Slider_SpeckleWindowSizeSG->setMaximum(255);
        Slider_SpeckleWindowSizeSG->setValue(100);
        Slider_SpeckleWindowSizeSG->setOrientation(Qt::Horizontal);
        Slider_SpeckleRangeSG = new QSlider(frame_26);
        Slider_SpeckleRangeSG->setObjectName(QString::fromUtf8("Slider_SpeckleRangeSG"));
        Slider_SpeckleRangeSG->setGeometry(QRect(180, 160, 171, 31));
        Slider_SpeckleRangeSG->setMaximum(100);
        Slider_SpeckleRangeSG->setValue(32);
        Slider_SpeckleRangeSG->setOrientation(Qt::Horizontal);
        Slider_SpeckleRangeSG->setTickPosition(QSlider::NoTicks);
        Slider_SpeckleRangeSG->setTickInterval(0);
        Slider_SADWindowSizeSG = new QSlider(frame_26);
        Slider_SADWindowSizeSG->setObjectName(QString::fromUtf8("Slider_SADWindowSizeSG"));
        Slider_SADWindowSizeSG->setGeometry(QRect(180, 190, 171, 31));
        Slider_SADWindowSizeSG->setMinimum(5);
        Slider_SADWindowSizeSG->setMaximum(255);
        Slider_SADWindowSizeSG->setValue(9);
        Slider_SADWindowSizeSG->setOrientation(Qt::Horizontal);
        SADWindowSizeSG = new QLabel(frame_26);
        SADWindowSizeSG->setObjectName(QString::fromUtf8("SADWindowSizeSG"));
        SADWindowSizeSG->setGeometry(QRect(20, 190, 131, 31));
        BMParameter_2 = new QLabel(frame_26);
        BMParameter_2->setObjectName(QString::fromUtf8("BMParameter_2"));
        BMParameter_2->setGeometry(QRect(20, 10, 181, 17));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        BMParameter_2->setFont(font);
        label_NumberOfDisparitiesSG = new QLabel(frame_26);
        label_NumberOfDisparitiesSG->setObjectName(QString::fromUtf8("label_NumberOfDisparitiesSG"));
        label_NumberOfDisparitiesSG->setGeometry(QRect(360, 70, 41, 31));
        label_UniquenessRatioSG = new QLabel(frame_26);
        label_UniquenessRatioSG->setObjectName(QString::fromUtf8("label_UniquenessRatioSG"));
        label_UniquenessRatioSG->setGeometry(QRect(360, 100, 41, 31));
        label_SpeckleWindowSizeSG = new QLabel(frame_26);
        label_SpeckleWindowSizeSG->setObjectName(QString::fromUtf8("label_SpeckleWindowSizeSG"));
        label_SpeckleWindowSizeSG->setGeometry(QRect(360, 130, 41, 31));
        label_MinDisparitySG = new QLabel(frame_26);
        label_MinDisparitySG->setObjectName(QString::fromUtf8("label_MinDisparitySG"));
        label_MinDisparitySG->setGeometry(QRect(360, 40, 41, 31));
        label_SpeckleRangeSG = new QLabel(frame_26);
        label_SpeckleRangeSG->setObjectName(QString::fromUtf8("label_SpeckleRangeSG"));
        label_SpeckleRangeSG->setGeometry(QRect(360, 160, 41, 31));
        label_SADWindowSizeSG = new QLabel(frame_26);
        label_SADWindowSizeSG->setObjectName(QString::fromUtf8("label_SADWindowSizeSG"));
        label_SADWindowSizeSG->setGeometry(QRect(360, 190, 41, 31));
        frame_25 = new QFrame(centralWidget);
        frame_25->setObjectName(QString::fromUtf8("frame_25"));
        frame_25->setGeometry(QRect(1080, 310, 411, 321));
        frame_25->setFrameShape(QFrame::StyledPanel);
        frame_25->setFrameShadow(QFrame::Raised);
        Slider_PreFilterCap = new QSlider(frame_25);
        Slider_PreFilterCap->setObjectName(QString::fromUtf8("Slider_PreFilterCap"));
        Slider_PreFilterCap->setGeometry(QRect(180, 40, 171, 31));
        Slider_PreFilterCap->setMinimum(1);
        Slider_PreFilterCap->setMaximum(63);
        Slider_PreFilterCap->setValue(31);
        Slider_PreFilterCap->setOrientation(Qt::Horizontal);
        PreFilterCap = new QLabel(frame_25);
        PreFilterCap->setObjectName(QString::fromUtf8("PreFilterCap"));
        PreFilterCap->setGeometry(QRect(20, 40, 111, 31));
        SADWindowSize = new QLabel(frame_25);
        SADWindowSize->setObjectName(QString::fromUtf8("SADWindowSize"));
        SADWindowSize->setGeometry(QRect(20, 100, 131, 31));
        NumberOfDisparities = new QLabel(frame_25);
        NumberOfDisparities->setObjectName(QString::fromUtf8("NumberOfDisparities"));
        NumberOfDisparities->setGeometry(QRect(20, 160, 161, 31));
        TextureThreshold = new QLabel(frame_25);
        TextureThreshold->setObjectName(QString::fromUtf8("TextureThreshold"));
        TextureThreshold->setGeometry(QRect(20, 190, 131, 31));
        UniquenessRatio = new QLabel(frame_25);
        UniquenessRatio->setObjectName(QString::fromUtf8("UniquenessRatio"));
        UniquenessRatio->setGeometry(QRect(20, 220, 131, 31));
        SpeckleWindowSize = new QLabel(frame_25);
        SpeckleWindowSize->setObjectName(QString::fromUtf8("SpeckleWindowSize"));
        SpeckleWindowSize->setGeometry(QRect(20, 250, 171, 31));
        SpeckleRange = new QLabel(frame_25);
        SpeckleRange->setObjectName(QString::fromUtf8("SpeckleRange"));
        SpeckleRange->setGeometry(QRect(20, 280, 111, 31));
        PreFilterSize = new QLabel(frame_25);
        PreFilterSize->setObjectName(QString::fromUtf8("PreFilterSize"));
        PreFilterSize->setGeometry(QRect(20, 70, 111, 31));
        MinDisparity = new QLabel(frame_25);
        MinDisparity->setObjectName(QString::fromUtf8("MinDisparity"));
        MinDisparity->setGeometry(QRect(20, 130, 111, 31));
        Slider_PreFilterSize = new QSlider(frame_25);
        Slider_PreFilterSize->setObjectName(QString::fromUtf8("Slider_PreFilterSize"));
        Slider_PreFilterSize->setGeometry(QRect(180, 70, 171, 31));
        Slider_PreFilterSize->setMinimum(5);
        Slider_PreFilterSize->setMaximum(255);
        Slider_PreFilterSize->setSingleStep(2);
        Slider_PreFilterSize->setOrientation(Qt::Horizontal);
        Slider_MinDisparity = new QSlider(frame_25);
        Slider_MinDisparity->setObjectName(QString::fromUtf8("Slider_MinDisparity"));
        Slider_MinDisparity->setGeometry(QRect(180, 130, 171, 31));
        Slider_MinDisparity->setMinimum(-100);
        Slider_MinDisparity->setMaximum(100);
        Slider_MinDisparity->setValue(0);
        Slider_MinDisparity->setSliderPosition(0);
        Slider_MinDisparity->setOrientation(Qt::Horizontal);
        Slider_SADWindowSize = new QSlider(frame_25);
        Slider_SADWindowSize->setObjectName(QString::fromUtf8("Slider_SADWindowSize"));
        Slider_SADWindowSize->setGeometry(QRect(180, 100, 171, 31));
        Slider_SADWindowSize->setMinimum(5);
        Slider_SADWindowSize->setMaximum(255);
        Slider_SADWindowSize->setValue(9);
        Slider_SADWindowSize->setOrientation(Qt::Horizontal);
        Slider_NumberOfDisparities = new QSlider(frame_25);
        Slider_NumberOfDisparities->setObjectName(QString::fromUtf8("Slider_NumberOfDisparities"));
        Slider_NumberOfDisparities->setGeometry(QRect(180, 160, 171, 31));
        Slider_NumberOfDisparities->setMinimum(16);
        Slider_NumberOfDisparities->setMaximum(256);
        Slider_NumberOfDisparities->setSingleStep(16);
        Slider_NumberOfDisparities->setPageStep(16);
        Slider_NumberOfDisparities->setValue(48);
        Slider_NumberOfDisparities->setOrientation(Qt::Horizontal);
        Slider_NumberOfDisparities->setTickPosition(QSlider::TicksBelow);
        Slider_NumberOfDisparities->setTickInterval(16);
        Slider_TextureThreshold = new QSlider(frame_25);
        Slider_TextureThreshold->setObjectName(QString::fromUtf8("Slider_TextureThreshold"));
        Slider_TextureThreshold->setGeometry(QRect(180, 190, 171, 31));
        Slider_TextureThreshold->setMaximum(500);
        Slider_TextureThreshold->setValue(10);
        Slider_TextureThreshold->setOrientation(Qt::Horizontal);
        Slider_UniquenessRatio = new QSlider(frame_25);
        Slider_UniquenessRatio->setObjectName(QString::fromUtf8("Slider_UniquenessRatio"));
        Slider_UniquenessRatio->setGeometry(QRect(180, 220, 171, 31));
        Slider_UniquenessRatio->setMaximum(100);
        Slider_UniquenessRatio->setValue(15);
        Slider_UniquenessRatio->setOrientation(Qt::Horizontal);
        Slider_SpeckleWindowSize = new QSlider(frame_25);
        Slider_SpeckleWindowSize->setObjectName(QString::fromUtf8("Slider_SpeckleWindowSize"));
        Slider_SpeckleWindowSize->setGeometry(QRect(180, 250, 171, 31));
        Slider_SpeckleWindowSize->setMaximum(255);
        Slider_SpeckleWindowSize->setValue(100);
        Slider_SpeckleWindowSize->setOrientation(Qt::Horizontal);
        Slider_SpeckleRange = new QSlider(frame_25);
        Slider_SpeckleRange->setObjectName(QString::fromUtf8("Slider_SpeckleRange"));
        Slider_SpeckleRange->setGeometry(QRect(180, 280, 171, 31));
        Slider_SpeckleRange->setMaximum(100);
        Slider_SpeckleRange->setValue(32);
        Slider_SpeckleRange->setOrientation(Qt::Horizontal);
        Slider_SpeckleRange->setTickPosition(QSlider::NoTicks);
        Slider_SpeckleRange->setTickInterval(0);
        BMParameter = new QLabel(frame_25);
        BMParameter->setObjectName(QString::fromUtf8("BMParameter"));
        BMParameter->setGeometry(QRect(20, 10, 181, 17));
        BMParameter->setFont(font);
        label_MinDisparity = new QLabel(frame_25);
        label_MinDisparity->setObjectName(QString::fromUtf8("label_MinDisparity"));
        label_MinDisparity->setGeometry(QRect(360, 130, 41, 31));
        label_NumberOfDisparities = new QLabel(frame_25);
        label_NumberOfDisparities->setObjectName(QString::fromUtf8("label_NumberOfDisparities"));
        label_NumberOfDisparities->setGeometry(QRect(360, 160, 41, 31));
        label_PreFilterSize = new QLabel(frame_25);
        label_PreFilterSize->setObjectName(QString::fromUtf8("label_PreFilterSize"));
        label_PreFilterSize->setGeometry(QRect(360, 70, 41, 31));
        label_SpeckleRange = new QLabel(frame_25);
        label_SpeckleRange->setObjectName(QString::fromUtf8("label_SpeckleRange"));
        label_SpeckleRange->setGeometry(QRect(360, 280, 41, 31));
        label_SpeckleWindowSize = new QLabel(frame_25);
        label_SpeckleWindowSize->setObjectName(QString::fromUtf8("label_SpeckleWindowSize"));
        label_SpeckleWindowSize->setGeometry(QRect(360, 250, 41, 31));
        label_TextureThreshold = new QLabel(frame_25);
        label_TextureThreshold->setObjectName(QString::fromUtf8("label_TextureThreshold"));
        label_TextureThreshold->setGeometry(QRect(360, 190, 41, 31));
        label_SADWindowSize = new QLabel(frame_25);
        label_SADWindowSize->setObjectName(QString::fromUtf8("label_SADWindowSize"));
        label_SADWindowSize->setGeometry(QRect(360, 100, 41, 31));
        label_PreFilterCap = new QLabel(frame_25);
        label_PreFilterCap->setObjectName(QString::fromUtf8("label_PreFilterCap"));
        label_PreFilterCap->setGeometry(QRect(360, 40, 41, 31));
        label_UniquenessRatio = new QLabel(frame_25);
        label_UniquenessRatio->setObjectName(QString::fromUtf8("label_UniquenessRatio"));
        label_UniquenessRatio->setGeometry(QRect(360, 220, 41, 31));
        verticalLayoutWidget_13 = new QWidget(centralWidget);
        verticalLayoutWidget_13->setObjectName(QString::fromUtf8("verticalLayoutWidget_13"));
        verticalLayoutWidget_13->setGeometry(QRect(1370, 670, 128, 211));
        verticalLayout_24 = new QVBoxLayout(verticalLayoutWidget_13);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(0, 0, 0, 0);
        pb_reset = new QPushButton(verticalLayoutWidget_13);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));

        verticalLayout_24->addWidget(pb_reset);

        ResetViewButton = new QPushButton(verticalLayoutWidget_13);
        ResetViewButton->setObjectName(QString::fromUtf8("ResetViewButton"));

        verticalLayout_24->addWidget(ResetViewButton);

        LocalImageModeButton = new QPushButton(verticalLayoutWidget_13);
        LocalImageModeButton->setObjectName(QString::fromUtf8("LocalImageModeButton"));

        verticalLayout_24->addWidget(LocalImageModeButton);

        RealTimeModeButton = new QPushButton(verticalLayoutWidget_13);
        RealTimeModeButton->setObjectName(QString::fromUtf8("RealTimeModeButton"));

        verticalLayout_24->addWidget(RealTimeModeButton);

        ExitButton = new QPushButton(verticalLayoutWidget_13);
        ExitButton->setObjectName(QString::fromUtf8("ExitButton"));

        verticalLayout_24->addWidget(ExitButton);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(1070, 670, 128, 211));
        verticalLayout_11 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(0, 0, 0, 0);
        cb_auto_update = new QCheckBox(verticalLayoutWidget_2);
        cb_auto_update->setObjectName(QString::fromUtf8("cb_auto_update"));
        cb_auto_update->setChecked(false);

        verticalLayout_11->addWidget(cb_auto_update);

        BackgroundCheckBox = new QCheckBox(verticalLayoutWidget_2);
        BackgroundCheckBox->setObjectName(QString::fromUtf8("BackgroundCheckBox"));
        BackgroundCheckBox->setAcceptDrops(false);
        BackgroundCheckBox->setChecked(true);

        verticalLayout_11->addWidget(BackgroundCheckBox);

        ShowCameraCheckBox = new QCheckBox(verticalLayoutWidget_2);
        ShowCameraCheckBox->setObjectName(QString::fromUtf8("ShowCameraCheckBox"));
        ShowCameraCheckBox->setEnabled(true);
        ShowCameraCheckBox->setMouseTracking(true);
        ShowCameraCheckBox->setChecked(true);

        verticalLayout_11->addWidget(ShowCameraCheckBox);

        FollowCameraCheckBox = new QCheckBox(verticalLayoutWidget_2);
        FollowCameraCheckBox->setObjectName(QString::fromUtf8("FollowCameraCheckBox"));
        FollowCameraCheckBox->setEnabled(true);
        FollowCameraCheckBox->setChecked(true);

        verticalLayout_11->addWidget(FollowCameraCheckBox);

        RecordCheckBox = new QCheckBox(verticalLayoutWidget_2);
        RecordCheckBox->setObjectName(QString::fromUtf8("RecordCheckBox"));

        verticalLayout_11->addWidget(RecordCheckBox);

        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(1220, 670, 128, 211));
        verticalLayout_14 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        DisparityModeBox = new QComboBox(verticalLayoutWidget_3);
        DisparityModeBox->setObjectName(QString::fromUtf8("DisparityModeBox"));

        verticalLayout_14->addWidget(DisparityModeBox);

        SaveVideoButton = new QPushButton(verticalLayoutWidget_3);
        SaveVideoButton->setObjectName(QString::fromUtf8("SaveVideoButton"));

        verticalLayout_14->addWidget(SaveVideoButton);

        ShowPosesButton = new QPushButton(verticalLayoutWidget_3);
        ShowPosesButton->setObjectName(QString::fromUtf8("ShowPosesButton"));

        verticalLayout_14->addWidget(ShowPosesButton);

        DeletePoseButton = new QPushButton(verticalLayoutWidget_3);
        DeletePoseButton->setObjectName(QString::fromUtf8("DeletePoseButton"));

        verticalLayout_14->addWidget(DeletePoseButton);

        AddPoseButton = new QPushButton(verticalLayoutWidget_3);
        AddPoseButton->setObjectName(QString::fromUtf8("AddPoseButton"));

        verticalLayout_14->addWidget(AddPoseButton);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(Slider_MinDisparitySG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_MinDisparitySG(int)));
        QObject::connect(Slider_NumberOfDisparitiesSG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_NumberOfDisparitiesSG(int)));
        QObject::connect(Slider_UniquenessRatioSG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_UniquenessRatioSG(int)));
        QObject::connect(Slider_SpeckleWindowSizeSG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SpeckleWindowSizeSG(int)));
        QObject::connect(Slider_SpeckleRangeSG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SpeckleRangeSG(int)));
        QObject::connect(Slider_SADWindowSizeSG, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SADWindowSizeSG(int)));
        QObject::connect(Slider_PreFilterCap, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_PreFilterCap(int)));
        QObject::connect(Slider_PreFilterSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_PreFilterSize(int)));
        QObject::connect(Slider_SADWindowSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SADWindowSize(int)));
        QObject::connect(Slider_MinDisparity, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_MinDisparity(int)));
        QObject::connect(Slider_NumberOfDisparities, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_NumberOfDisparities(int)));
        QObject::connect(Slider_TextureThreshold, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_TextureThreshold(int)));
        QObject::connect(Slider_UniquenessRatio, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_UniquenessRatio(int)));
        QObject::connect(Slider_SpeckleWindowSize, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SpeckleWindowSize(int)));
        QObject::connect(Slider_SpeckleRange, SIGNAL(valueChanged(int)), MainWindow, SLOT(slot_slider_SpeckleRange(int)));
        QObject::connect(cb_auto_update, SIGNAL(stateChanged(int)), MainWindow, SLOT(slot_auto_update()));
        QObject::connect(pb_reset, SIGNAL(clicked()), MainWindow, SLOT(slot_reset()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        LeftImageLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MainWindow", "Map-Raw", 0, QApplication::UnicodeUTF8));
        ElasDepthImage->setText(QString());
        SGBMDepthImage->setText(QString());
        BMDepthImage->setText(QString());
        label_1->setText(QApplication::translate("MainWindow", "ELAS", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "BM", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "SGBM", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Depth", 0, QApplication::UnicodeUTF8));
        NumberOfDisparitiesSG->setText(QApplication::translate("MainWindow", "NumberOfDisparities", 0, QApplication::UnicodeUTF8));
        UniquenessRatioSG->setText(QApplication::translate("MainWindow", "UniquenessRatio", 0, QApplication::UnicodeUTF8));
        SpeckleWindowSizeSG->setText(QApplication::translate("MainWindow", "SpeckleWindowSize", 0, QApplication::UnicodeUTF8));
        SpeckleRangeSG->setText(QApplication::translate("MainWindow", "SpeckleRange", 0, QApplication::UnicodeUTF8));
        MinDisparitySG->setText(QApplication::translate("MainWindow", "MinDisparity", 0, QApplication::UnicodeUTF8));
        SADWindowSizeSG->setText(QApplication::translate("MainWindow", "SADWindowSize", 0, QApplication::UnicodeUTF8));
        BMParameter_2->setText(QApplication::translate("MainWindow", "SGBM-Parameter", 0, QApplication::UnicodeUTF8));
        label_NumberOfDisparitiesSG->setText(QString());
        label_UniquenessRatioSG->setText(QString());
        label_SpeckleWindowSizeSG->setText(QString());
        label_MinDisparitySG->setText(QString());
        label_SpeckleRangeSG->setText(QString());
        label_SADWindowSizeSG->setText(QString());
        PreFilterCap->setText(QApplication::translate("MainWindow", "PreFilterCap", 0, QApplication::UnicodeUTF8));
        SADWindowSize->setText(QApplication::translate("MainWindow", "SADWindowSize", 0, QApplication::UnicodeUTF8));
        NumberOfDisparities->setText(QApplication::translate("MainWindow", "NumberOfDisparities", 0, QApplication::UnicodeUTF8));
        TextureThreshold->setText(QApplication::translate("MainWindow", "TextureThreshold", 0, QApplication::UnicodeUTF8));
        UniquenessRatio->setText(QApplication::translate("MainWindow", "UniquenessRatio", 0, QApplication::UnicodeUTF8));
        SpeckleWindowSize->setText(QApplication::translate("MainWindow", "SpeckleWindowSize", 0, QApplication::UnicodeUTF8));
        SpeckleRange->setText(QApplication::translate("MainWindow", "SpeckleRange", 0, QApplication::UnicodeUTF8));
        PreFilterSize->setText(QApplication::translate("MainWindow", "PreFilterSize", 0, QApplication::UnicodeUTF8));
        MinDisparity->setText(QApplication::translate("MainWindow", "MinDisparity", 0, QApplication::UnicodeUTF8));
        BMParameter->setText(QApplication::translate("MainWindow", "BM-Parameter", 0, QApplication::UnicodeUTF8));
        label_MinDisparity->setText(QString());
        label_NumberOfDisparities->setText(QString());
        label_PreFilterSize->setText(QString());
        label_SpeckleRange->setText(QString());
        label_SpeckleWindowSize->setText(QString());
        label_TextureThreshold->setText(QString());
        label_SADWindowSize->setText(QString());
        label_PreFilterCap->setText(QString());
        label_UniquenessRatio->setText(QString());
        pb_reset->setText(QApplication::translate("MainWindow", "ResetParameter", 0, QApplication::UnicodeUTF8));
        ResetViewButton->setText(QApplication::translate("MainWindow", "ResetView", 0, QApplication::UnicodeUTF8));
        LocalImageModeButton->setText(QApplication::translate("MainWindow", "LocalImageMode", 0, QApplication::UnicodeUTF8));
        RealTimeModeButton->setText(QApplication::translate("MainWindow", "RealTimeMode", 0, QApplication::UnicodeUTF8));
        ExitButton->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        cb_auto_update->setText(QApplication::translate("MainWindow", "Auto-Update", 0, QApplication::UnicodeUTF8));
        BackgroundCheckBox->setText(QApplication::translate("MainWindow", "Background", 0, QApplication::UnicodeUTF8));
        ShowCameraCheckBox->setText(QApplication::translate("MainWindow", "ShowCamera", 0, QApplication::UnicodeUTF8));
        FollowCameraCheckBox->setText(QApplication::translate("MainWindow", "FollowCamera", 0, QApplication::UnicodeUTF8));
        RecordCheckBox->setText(QApplication::translate("MainWindow", "Record", 0, QApplication::UnicodeUTF8));
        DisparityModeBox->clear();
        DisparityModeBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "     Elas-Mode", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "    SGBM-Mode", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "     BM-Mode", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "     SPS-Mode", 0, QApplication::UnicodeUTF8)
        );
        SaveVideoButton->setText(QApplication::translate("MainWindow", "SaveVideo", 0, QApplication::UnicodeUTF8));
        ShowPosesButton->setText(QApplication::translate("MainWindow", "ShowPoses", 0, QApplication::UnicodeUTF8));
        DeletePoseButton->setText(QApplication::translate("MainWindow", "DeletePose", 0, QApplication::UnicodeUTF8));
        AddPoseButton->setText(QApplication::translate("MainWindow", "AddPose", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
