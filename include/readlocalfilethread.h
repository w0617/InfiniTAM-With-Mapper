#ifndef READLOCALFILETHREAD_H
#define READLOCALFILETHREAD_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>
#include <QtGui/QImage>
#include "include/calibrationparameters.h"
#include "include/stereoimage.h"
#include "libviso2/src/timer.h"

//Default path of local files.
//dadao dataset
const static std::string DADAO_CALIB_PATH = "/StereoCalib.yml";
const static std::string DADAO_POSE_AND_TIMESTAMPS_FILE_PATH = "/CamTics.txt";

//kitti dataset
const static std::string KITTI_CALIB_PATH = "/calib.txt";
const static std::string KITTI_TIMESTAMPS_FILE_PATH = "/times.txt";
const static std::string KITTI_POSE_FILE_PATH = "/poses.txt";


class ReadLocalFileThread : public QThread
{
    Q_OBJECT

public:

    //Constructer, the parameters are pointers from the main thread.
    ReadLocalFileThread(CalibrationParameters *calib,
                        StereoImage *stereo,
                        QObject *parent = 0);
    ~ReadLocalFileThread();

    bool SetInputDirectory(QString inputDirectory);

    std::string m_dadaoPoseAndTimestampsFilePath ;
    std::string m_dadaoImagePath;

    std::string m_kittiCalibFilePath;
    std::string m_kittiPoseFilePath;
    std::string m_kittiTimestampsFilePath;
    std::string m_kittiImagePath;

    //Show what running dataset now
    QString m_runningDataset;

    //check whether get pose
    bool CheckPoseFileStatus(){return m_poseFileExist;}
    bool CheckReadingStatus(){return m_endReading;}

protected:

    void run();

private:

    //Pointers in this thread, to send calibration parameters and stereo images.
    CalibrationParameters *m_calib;
    StereoImage *m_stereo;
    QString m_inputDirectory;

    //flag of pose file
    bool m_poseFileExist;

    bool m_endReading;

signals:


public slots:

};

#endif // READLOCALFILETHREAD_H
