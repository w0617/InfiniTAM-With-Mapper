#include "include/mainwindow.h"
#include "include/stereoimage.h"
#include <QtGui/QApplication>
#include <GL/glut.h>

int main(int argc, char *argv[])
{   
    StereoImage::saveDisparity = false;
    StereoImage::loadWaitDisparity = false;
    StereoImage::showDisparityImage = true;
    StereoImage::computeDisparityMode = ELAS_MODE;

    StereoImage::useInfiniTAM = true;
    StereoImage::infinitamWaitDisparity = true;

    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Mapper");
    w.show();
    
    //printf("\n++++++++++++++++++++\n\n");
    
    //========InifiTAM=======//
    if(StereoImage::useInfiniTAM)
        glutInit(&argc, argv);
    
    return a.exec();
}
