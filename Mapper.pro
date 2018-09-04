#-------------------------------------------------
#
# Project created by QtCreator 2018-06-01T09:59:14
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mapper
TEMPLATE = app
DESTDIR += ../bin

#includepath setting here, change it to your own setting
INCLUDEPATH +=  /usr/include/eigen3 \
                /usr/local/include/pangolin \
                /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2 \
                /home/w/Desktop/SLAM/ORB_SLAM2/include

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  src/main.cpp\
            src/mainwindow.cpp \
            src/calibrationparameters.cpp \
            src/stereoimage.cpp \
            src/readlocalfilethread.cpp \
            src/modelpainting.cpp \
            Disparity/libelas/src/descriptor.cpp \
            Disparity/libelas/src/elas.cpp \
            libviso2/src/filter.cpp \
            libviso2/src/matcher.cpp \
            libviso2/src/matrix.cpp \
            libviso2/src/triangle.cpp \
            libviso2/src/viso.cpp \
            libviso2/src/viso_stereo.cpp \
            src/reconstructionthread.cpp \
            src/getcameraposethread.cpp \
            src/realtimecamthread.cpp \
            Disparity/BM_SGBM/blockmatching.cpp \
            Disparity/BM_SGBM/sgblockmatching.cpp \
            Disparity/SPS_Stereo/SGMStereo.cpp \
            Disparity/SPS_Stereo/SPSStereo.cpp

HEADERS  += include/mainwindow.h \
            include/calibrationparameters.h \
            include/stereoimage.h \
            include/readlocalfilethread.h \
            include/modelpainting.h \
            Disparity/libelas/src/descriptor.h \
            Disparity/libelas/src/elas.h \
            libviso2/src/filter.h \
            libviso2/src/matcher.h \
            libviso2/src/matrix.h \
            libviso2/src/timer.h \
            libviso2/src/triangle.h \
            libviso2/src/viso.h \
            libviso2/src/viso_stereo.h \
            include/reconstructionthread.h \
            include/getcameraposethread.h \
            include/realtimecamthread.h \
           # loitorimu.h \
           # loitorusbcam.h \
            Disparity/BM_SGBM/blockmatching.h \
            Disparity/BM_SGBM/sgblockmatching.h \
            Disparity/SPS_Stereo/SGMStereo.h \
            Disparity/SPS_Stereo/SPSStereo.h \
            Disparity/SPS_Stereo/defParameter.h


FORMS    += ui/mainwindow.ui


#lib setting here, change it to your own setting
LIBS += -lglut -lGLU \
       # -L/usr/local/opencv/lib \
        #-lopencv_core\
        #-lopencv_highgui\
        #-lopencv_imgproc\
        #-lopencv_imgcodecs\
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_imgcodecs.so \
        -L"/usr/lib/x85_64-linux-gnu" -lexpat \
       # /home/w/Desktop/Reconstruction/Mapper/libloitorusbcam.a \
       # /home/w/Desktop/Reconstruction/Mapper/libloitorimu.a \
        #/home/w/Desktop/SLAM/ORB_SLAM2/lib/libORB_SLAM2.so \
        -lusb-1.0 \
        -L/home/w/Desktop/SLAM/ORB_SLAM2/lib -lORB_SLAM2 \
        -L/home/w/Desktop/SLAM/ORB_SLAM2/Thirdparty/g2o/lib -lg2o \
        -L/home/w/Desktop/SLAM/ORB_SLAM2/Thirdparty/DBoW2/lib -lDBoW2 \
        -L/usr/local/lib -lpangolin

UI_HEADERS_DIR = ../ui
UI_SOURCES_DIR = ../ui
MOC_DIR = ../src/moc

QMAKE_CXXFLAGS += -O3 -pipe -fomit-frame-pointer -msse4.2 -std=c++11 #-msse3  -std=c++0x
