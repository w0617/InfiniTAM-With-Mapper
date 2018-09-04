#include "include/calibrationparameters.h"


CalibrationParameters::CalibrationParameters(QObject *parent) : QObject(parent)
{
    m_runningDataType = OTHER_DATASET_FLAG;
}

CalibrationParameters::~CalibrationParameters()
{

}

//Get dadao dataset opencv calibration parameters.
//The parameter is the path of opencv calib file.
bool CalibrationParameters::GetDadaoCalibParam(string pathOfDadaoCalibFile)
{
    cv::FileStorage fs;
    fs.open(pathOfDadaoCalibFile, cv::FileStorage::READ);

    // if failed to open a file
    if(!fs.isOpened())
    {
        std::cout<<"Failed to read file 'StereoCalib.yml'(dadao calib file). "<<std::endl;
        return false;
    }
    else
    {
        fs["DateAndTime"]>>m_dadaoCalibParam.m_calib_time;
        fs["ImageHeight"]>>m_dadaoCalibParam.m_ImageHeight;
        fs["ImageWidth"]>>m_dadaoCalibParam.m_ImageWidth;
        if (m_dadaoCalibParam.m_ImageHeight<0 || m_dadaoCalibParam.m_ImageHeight<0)
        {
            std::cout<<"Opencv calibration file is not correct."<<std::endl;
            return false;
        }
        fs["CM1"]>>m_dadaoCalibParam.m_CM1;
        fs["CM2"]>>m_dadaoCalibParam.m_CM2;
        fs["D1"]>>m_dadaoCalibParam.m_D1;
        fs["D2"]>>m_dadaoCalibParam.m_D2;
        fs["R"]>>m_dadaoCalibParam.m_R;
        fs["T"]>>m_dadaoCalibParam.m_T;
        fs["E"]>>m_dadaoCalibParam.m_E;
        fs["F"]>>m_dadaoCalibParam.m_F;
        fs["R1"]>>m_dadaoCalibParam.m_R1;
        fs["R2"]>>m_dadaoCalibParam.m_R2;
        fs["P1"]>>m_dadaoCalibParam.m_P1;
        fs["P2"]>>m_dadaoCalibParam.m_P2;
        fs["Q"]>>m_dadaoCalibParam.m_Q;
        fs["ROI_top"] >> m_dadaoCalibParam.m_ROI.y;
        fs["ROI_left"] >> m_dadaoCalibParam.m_ROI.x;
        fs["ROI_right"] >> m_dadaoCalibParam.m_ROI.width;
        fs["ROI_bottom"] >> m_dadaoCalibParam.m_ROI.height;
        fs["Left_Mapping_1"]>>m_dadaoCalibParam.m_Left_Mapping_1;
        fs["Left_Mapping_2"]>>m_dadaoCalibParam.m_Left_Mapping_2;
        fs["Right_Mapping_1"]>>m_dadaoCalibParam.m_Right_Mapping_1;
        fs["Right_Mapping_2"]>>m_dadaoCalibParam.m_Right_Mapping_2;

        m_dadaoCalibParam.m_ROI.height -= m_dadaoCalibParam.m_ROI.y;
        m_dadaoCalibParam.m_ROI.width -= m_dadaoCalibParam.m_ROI.x;

        m_dadaoCalibParam.m_f = m_dadaoCalibParam.m_P1.at<double>(0,0);
        m_dadaoCalibParam.m_cu = m_dadaoCalibParam.m_P1.at<double>(0,2);
        m_dadaoCalibParam.m_cv = m_dadaoCalibParam.m_P1.at<double>(1,2);
        m_dadaoCalibParam.m_baseline = -(m_dadaoCalibParam.m_P2.at<double>(0,3)/m_dadaoCalibParam.m_f);
        std::cout<<"Read file 'StereoCalib.yml'(dadao calib file) success."<<std::endl;
        m_runningDataType = DADAO_DATASET_FLAG;
    }

    m_pickedNewCalibParam = false;
    emit DetectNewCalibParam();
    while (!m_pickedNewCalibParam) usleep(1000);

    fs.release();
    return true;
}

bool CalibrationParameters::GetKittiCalibParam(string pathOfKittiCalibFile)
{    
    std::vector<double> kittiParam;
    char line[1000];
    FILE * pFile;
    const char *path=pathOfKittiCalibFile.c_str();
    pFile = fopen (path,"r");
    if (NULL == pFile)
    {
        std::cout<<"Failed to read file 'calib.txt'(kitti calib file). "<<std::endl;
        return false;
    }

    if (pFile!=NULL)
    {
        while(1)
        {
            if (fgets (line, 1000, pFile)==NULL)
                break;
            // 分割每行
            const char* fliter = " ";
            const char* pch = strtok (line, fliter);

            while (pch != NULL)
            {
                double val = atof(pch);
                kittiParam.push_back(val);
                // 继续分割
                pch = strtok (NULL, fliter);
            }
        }
        fclose (pFile);
    }
    m_KittiCalibParam.m_f = kittiParam[1];
    m_KittiCalibParam.m_cu = kittiParam[3];
    m_KittiCalibParam.m_cv = kittiParam[7];
    m_KittiCalibParam.m_baseline = -(kittiParam[17]/kittiParam[1]);
    std::cout<<"Read file 'calib.txt'(kitti calib file) success."<<std::endl;
    m_runningDataType = KITTI_DATASET_FLAG;

    m_pickedNewCalibParam = false;
    emit DetectNewCalibParam();
    while (!m_pickedNewCalibParam) usleep(1000);

    kittiParam.clear();
    return true;
}

bool CalibrationParameters::GetLoitorCalibParam(string pathOfLoitorCalibFile)
{
    cv::FileStorage fs;
    fs.open(pathOfLoitorCalibFile, cv::FileStorage::READ);

    // if failed to open a file
    if(!fs.isOpened())
    {
        std::cout<<"Failed to read file 'StereoCalib.yml'(loitor calib file). "<<std::endl;
        return false;
    }
    else
    {

        fs["P1"]>>m_loitorCalibParam.m_P1;
        fs["P2"]>>m_loitorCalibParam.m_P2;
        fs["Left_Mapping_1"]>>m_loitorCalibParam.m_Left_Mapping_1;
        fs["Left_Mapping_2"]>>m_loitorCalibParam.m_Left_Mapping_2;
        fs["Right_Mapping_1"]>>m_loitorCalibParam.m_Right_Mapping_1;
        fs["Right_Mapping_2"]>>m_loitorCalibParam.m_Right_Mapping_2;

        m_loitorCalibParam.m_f = m_loitorCalibParam.m_P1.at<double>(0,0);
        m_loitorCalibParam.m_cu = m_loitorCalibParam.m_P1.at<double>(0,2);
        m_loitorCalibParam.m_cv = m_loitorCalibParam.m_P1.at<double>(1,2);
        m_loitorCalibParam.m_baseline = -(m_loitorCalibParam.m_P2.at<double>(0,3)/m_loitorCalibParam.m_f);

        /*
        cv::Mat K_l, K_r, P_l, P_r, R_l, R_r, D_l, D_r;
        fs["LEFT.K"] >> K_l;
        fs["RIGHT.K"] >> K_r;

        fs["LEFT.P"] >> P_l;
        fs["RIGHT.P"] >> P_r;

        fs["LEFT.R"] >> R_l;
        fs["RIGHT.R"] >> R_r;

        fs["LEFT.D"] >> D_l;
        fs["RIGHT.D"] >> D_r;

        int rows_l = fs["LEFT.height"];
        int cols_l = fs["LEFT.width"];
        int rows_r = fs["RIGHT.height"];
        int cols_r = fs["RIGHT.width"];

        if(K_l.empty() || K_r.empty() || P_l.empty() || P_r.empty() || R_l.empty() || R_r.empty() || D_l.empty() || D_r.empty() ||
                rows_l==0 || rows_r==0 || cols_l==0 || cols_r==0)
        {
            cerr << "ERROR: Calibration parameters to rectify stereo are missing!" << endl;
            return -1;
        }

        cv::Mat M1l,M2l,M1r,M2r;
        cv::initUndistortRectifyMap(K_l,D_l,R_l,P_l.rowRange(0,3).colRange(0,3),cv::Size(cols_l,rows_l),CV_32F,M1l,M2l);
        cv::initUndistortRectifyMap(K_r,D_r,R_r,P_r.rowRange(0,3).colRange(0,3),cv::Size(cols_r,rows_r),CV_32F,M1r,M2r);

        m_loitorCalibParam.m_P1=P_l;
        m_loitorCalibParam.m_P2=P_r;
        m_loitorCalibParam.m_Left_Mapping_1=M1l;
        m_loitorCalibParam.m_Left_Mapping_2=M2l;
        m_loitorCalibParam.m_Right_Mapping_1=M1r;
        m_loitorCalibParam.m_Right_Mapping_2=M2r;

        m_loitorCalibParam.m_f = m_loitorCalibParam.m_P1.at<double>(0,0);
        m_loitorCalibParam.m_cu = m_loitorCalibParam.m_P1.at<double>(0,2);
        m_loitorCalibParam.m_cv = m_loitorCalibParam.m_P1.at<double>(1,2);
        m_loitorCalibParam.m_baseline = -(m_loitorCalibParam.m_P2.at<double>(0,3)/m_loitorCalibParam.m_f);
*/
        std::cout<<"Read file 'StereoCalib.yml'(loitor calib file) success(calibpointer)."<<std::endl;
    }
    m_runningDataType = LOITOR_DATASET_FLAG;

    m_pickedNewCalibParam = false;
    emit DetectNewCalibParam();
    while (!m_pickedNewCalibParam) usleep(1000);

    fs.release();
    return true;
}

