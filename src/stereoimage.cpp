#include "include/stereoimage.h"

using namespace std;

bool StereoImage::loadWaitDisparity = false;
bool StereoImage::saveDisparity = false;
bool StereoImage::showDisparityImage = true;
char StereoImage::computeDisparityMode = ELAS_MODE;

bool StereoImage::useInfiniTAM = true;
bool StereoImage::infinitamWaitDisparity = true;

StereoImage::StereoImageParameters* StereoImage::m_currentFrame = new StereoImage::StereoImageParameters();
double StereoImage::cameraFocus = 0;
double StereoImage::cameraBaseline = 0;


StereoImage::StereoImage(QObject *parent):QObject(parent)
{
    m_leftImage  = new SingleImage();
    m_rightImage = new SingleImage();
    m_stereoImage = new StereoImageParameters();

}

StereoImage::~StereoImage()
{
    if (m_leftImage!=0)   { delete m_leftImage;  m_leftImage  = 0; }
    if (m_rightImage!=0)  { delete m_rightImage; m_rightImage = 0; }
    if (m_stereoImage!=0) { delete m_stereoImage;  m_stereoImage = 0; }
    m_kittiCapturedTime.clear();
    m_dadaoCapturedTime.clear();
    m_kittiPoses.clear();
    m_dadaoPoses.clear();
}

//=================================================================================================//
//==================================DadaoDatasetFuntion============================================//
//=================================================================================================//

bool StereoImage::GetDadaoTimesAndPoses(string DadaoCamticsFilePath)
{
    std::vector<float> tempVec;
    m_numOfDadaoImage = -1;
    const char *path=DadaoCamticsFilePath.c_str();
    ifstream fin(path, ios::in);
    float data;
    while(fin)
    {
        fin >> data;
        tempVec.push_back(data);
        fin >> data;
        tempVec.push_back(data);
        fin >> data;
        tempVec.push_back(data);
        fin >> data;
        tempVec.push_back(data);
        fin >> data;
        tempVec.push_back(data);

        m_numOfDadaoImage++;
        m_dadaoCapturedTime.push_back(tempVec[1]);
        m_dadaoPoses.push_back(tempVec);
        tempVec.clear();
    }
    fin.close();

    /*
    char line[1000];
    FILE * pFile;
    pFile = fopen (path,"r");
    if (NULL == pFile)
    {
        std::cout<<"Failed to read file 'CamTics.txt'. "<<std::endl;
        return false;
    }

    if (pFile != NULL)
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
                float val = atof(pch);
                tempVec.push_back(val);
                // 继续分割
                pch = strtok (NULL, fliter);
            }
            m_dadaoCapturedTime.push_back(tempVec[1]);
            m_dadaoPoses.push_back(tempVec);
            m_numOfDadaoImage++;
            tempVec.clear();
        }
        fclose (pFile);
    }
    */

    std::cout<<"Read file 'CamTics.txt' success."<<std::endl;
    return true;
}

void StereoImage::GetDadaoImages(DadaoImage m_dadaoImage[], string m_dadaoImagePath, int index)
{
    m_frameindex = index;
    m_dadaoImage[0].m_capturedTime = m_dadaoCapturedTime[index];
    m_dadaoImage[1].m_capturedTime = m_dadaoCapturedTime[index];
    //std::cout<<index<<"--"<<m_kittiCapturedTime[index]<<std::endl;

    std::ostringstream ss;
    ss << std::setw(6) << std::setfill('0') << index << ".png";
    std::string leftImagePath = m_dadaoImagePath + "/left/" + ss.str();
    std::string rightImagePath = m_dadaoImagePath + "/right/" + ss.str();

    m_dadaoImage[0].m_rawImage = cv::imread(leftImagePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    m_dadaoImage[1].m_rawImage = cv::imread(rightImagePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

    cv::Mat tempLeftMat = m_dadaoImage[0].m_rawImage;
    //cv::Mat tempRightMat = cv::cvarrToMat(m_kittiImage[1].m_image);

    QImage tempLeftQImage(tempLeftMat.cols, tempLeftMat.rows, QImage::Format_Indexed8);
    //QImage tempRightQImage(tempRightMat.cols, tempRightMat.rows, QImage::Format_Indexed8);
    // Set the color table (used to translate colour indexes to qRgb values)
    tempLeftQImage.setColorCount(256);
    //tempRightQImage.setColorCount(256);
    for(int i = 0; i < 256; i++)
    {
       tempLeftQImage.setColor(i, qRgb(i, i, i));
       //tempRightQImage.setColor(i, qRgb(i, i, i));
    }
    // Copy input Mat
    uchar *pSrc = tempLeftMat.data;
    for(int row = 0; row < tempLeftMat.rows; row ++)
    {
       uchar *pDest = tempLeftQImage.scanLine(row);
       memcpy(pDest, pSrc, tempLeftMat.cols);
       pSrc += tempLeftMat.step;
    }
    /*
    uchar *pSrc_ = tempRightMat.data;
    for(int row = 0; row < tempRightMat.rows; row ++)
    {
       uchar *pDest_ = tempRightQImage.scanLine(row);
       memcpy(pDest_, pSrc_, tempRightMat.cols);
       pSrc_ += tempRightMat.step;
    }
    */
    m_displayLeftImage = tempLeftQImage;
}

//=================================================================================================//
//==================================KittiDatasetFuntion============================================//
//=================================================================================================//

bool StereoImage::GetKittiTimestamps(string kittiTimestampsFilePath)
{
    // Read the timestamp files.
    m_numOfKittiImage = 0;
    char line[1000];
    FILE * pFile;
    const char *path=kittiTimestampsFilePath.c_str();
    pFile = fopen (path,"r");
    if (NULL == pFile)
    {
        std::cout<<"Failed to read kitti timestamps file 'time.txt'. "<<std::endl;
        return false;
    }

    if (pFile != NULL)
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
                float val = atof(pch);
                m_kittiCapturedTime.push_back(val);
                m_numOfKittiImage++;
                // 继续分割
                pch = strtok (NULL, fliter);
            }
        }
        fclose (pFile);
    }

    std::cout<<"Read file 'times.txt'(kitti timestamps file) success."<<std::endl;
    return true;
}

bool StereoImage::GetKittiPoses(string kittiPosesFilePath)
{
    std::vector<float> tempPoses;
    char line[1000];
    FILE * pFile;
    const char *path=kittiPosesFilePath.c_str();
    pFile = fopen (path,"r");
    if (NULL == pFile)
    {
        std::cout<<"Failed to read kitti poses file 'poses.txt'. "<<std::endl;
        return false;
    }

    if (pFile != NULL)
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
                float val = atof(pch);
                tempPoses.push_back(val);
                // 继续分割
                pch = strtok (NULL, fliter);
            }
            m_kittiPoses.push_back(tempPoses);
            tempPoses.clear();
        }
        fclose (pFile);
    }
    tempPoses.clear();
    std::cout<<"Read kitti poses file 'poses.txt' success."<<std::endl;
    return true;
}

void StereoImage::GetKittiImages(KittiImage m_kittiImage[2], std::string m_kittiImagePath, int index)
{
    m_frameindex = index;
    m_kittiImage[0].m_capturedTime = m_kittiCapturedTime[index];
    m_kittiImage[1].m_capturedTime = m_kittiCapturedTime[index];
    //std::cout<<index<<"--"<<m_kittiCapturedTime[index]<<std::endl;

    std::ostringstream ss;
    ss << std::setw(6) << std::setfill('0') << index << ".png";
    std::string leftImagePath = m_kittiImagePath + "/image_0/" + ss.str();
    std::string rightImagePath = m_kittiImagePath + "/image_1/" + ss.str();

    m_kittiImage[0].m_image = cvLoadImage(leftImagePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
    m_kittiImage[1].m_image = cvLoadImage(rightImagePath.c_str(), CV_LOAD_IMAGE_GRAYSCALE);

    cv::Mat tempLeftMat = cv::cvarrToMat(m_kittiImage[0].m_image);
    //cv::Mat tempRightMat = cv::cvarrToMat(m_kittiImage[1].m_image);

    QImage tempLeftQImage(tempLeftMat.cols, tempLeftMat.rows, QImage::Format_Indexed8);
    //QImage tempRightQImage(tempRightMat.cols, tempRightMat.rows, QImage::Format_Indexed8);
    // Set the color table (used to translate colour indexes to qRgb values)
    tempLeftQImage.setColorCount(256);
    //tempRightQImage.setColorCount(256);
    for(int i = 0; i < 256; i++)
    {
       tempLeftQImage.setColor(i, qRgb(i, i, i));
       //tempRightQImage.setColor(i, qRgb(i, i, i));
    }
    // Copy input Mat
    uchar *pSrc = tempLeftMat.data;
    for(int row = 0; row < tempLeftMat.rows; row ++)
    {
       uchar *pDest = tempLeftQImage.scanLine(row);
       memcpy(pDest, pSrc, tempLeftMat.cols);
       pSrc += tempLeftMat.step;
    }
    /*
    uchar *pSrc_ = tempRightMat.data;
    for(int row = 0; row < tempRightMat.rows; row ++)
    {
       uchar *pDest_ = tempRightQImage.scanLine(row);
       memcpy(pDest_, pSrc_, tempRightMat.cols);
       pSrc_ += tempRightMat.step;
    }
    */
    m_displayLeftImage = tempLeftQImage;
    //m_displayRightImage = tempRightQImage;

}

//=================================================================================================//
//                                    Save depth of image (.pgm)                                   //
//=================================================================================================//
void StereoImage::SaveKittiDepthImages( std::string m_kittiImagePath, int index )
{
    float *addLeftDepth, *addRightDepth;
    uint temp;
    int width = m_currentFrame->width;
    int height = m_currentFrame->height;

    char num = 0;

    ofstream leftFile, rightFile;

    std::ostringstream ss;
    ss << std::setw(6) << std::setfill('0') << index << ".pgm";
    std::string leftImagePath = m_kittiImagePath + "/image_0/" + ss.str();
    std::string rightImagePath = m_kittiImagePath + "/image_1/" + ss.str();

    addLeftDepth = m_currentFrame->D1;
    addRightDepth = m_currentFrame->D2;

    leftFile.open( leftImagePath );
    leftFile << "P2"  << " " << width << " " << height << " " << 65535 << " " << endl;
    num = 0;
    for( int i = 0; i < height; i++)
    {
        for( int j = 0; j < width; j++)
        {
            temp =  ceil( 256*(/*cameraFocus*cameraBaseline/*/(*addLeftDepth)+10) );  //+X (ELAS:10, SPS:0)
            if( temp > 65535 ) temp = 65535;
            if( temp < 0 ) temp = 0;
            leftFile << temp << " ";
            ++addLeftDepth;
            if(++num > 70)
            {
                num = 0;
                leftFile << endl;
            }
        }
        num = 0;
        leftFile << endl;
    }
    leftFile.close();

    rightFile.open( rightImagePath );
    rightFile << "P2"  << " " << width << " " << height << " " << 65535 << " " << endl;
    num = 0;
    for( int i = 0; i < height; i++)
    {
        for( int j = 0; j < width; j++)
        {
            temp =  ceil( 256*(/*cameraFocus*cameraBaseline/*/(*addLeftDepth)+0) );
            if( temp > 65535 ) temp = 65535;
            if( temp < 0 ) temp = 0;
            rightFile << temp << " ";
            ++addRightDepth;
            if(++num > 70)
            {
                num = 0;
                rightFile << endl;
            }
        }
        num = 0;
        rightFile << endl;
    }
    rightFile.close();

    cout<< "Save depth to .pgm" <<endl<<endl;
}




//=================================================================================================//
//========================================CommonFuntion============================================//
//=================================================================================================//
//Copy the image from local file to memory.
//Save them as stereo image structure.
void StereoImage::SetStereoImage(unsigned char *imageData, int width, int height, int step, bool cam_left, double captured_time)
{

    // get pointer to data
    SingleImage *img = m_rightImage;

    if (cam_left)
    {
        img = m_leftImage;
    }

    //Initialization of memory.
    if (width!=img->width || height!=img->height || step!=img->step)
    {
        if (img->data!=0)
        {
            free(img->data);
            img->data = 0;
        }

        img->data   = (unsigned char*)malloc(step*height*sizeof(unsigned char));
        img->width  = width;
        img->height = height;
        img->step   = step;
    }

    // set timestamp
    img->time = captured_time;

    // copy data
    memcpy(img->data,imageData,step*height*sizeof(unsigned char));

    // do we have a valid stereo frame => copy it!
    if( m_leftImage->time == m_rightImage->time )
    {
        if (m_leftImage->width==m_rightImage->width && m_leftImage->height==m_rightImage->height && m_leftImage->step==m_rightImage->step)
        {
            // if width or height has changed => free old & allocate new memory block
            if (m_leftImage->width!=m_stereoImage->width || m_leftImage->height!=m_stereoImage->height || m_leftImage->step!=m_stereoImage->step)
            {
                if (m_stereoImage->I1!=0) { free(m_stereoImage->I1); m_stereoImage->I1 = 0; }
                if (m_stereoImage->I2!=0) { free(m_stereoImage->I2); m_stereoImage->I2 = 0; }
                m_stereoImage->I1     = (unsigned char*)malloc(m_leftImage->step*m_leftImage->height*sizeof(unsigned char));
                m_stereoImage->I2     = (unsigned char*)malloc(m_leftImage->step*m_leftImage->height*sizeof(unsigned char));
                m_stereoImage->width  = m_leftImage->width;
                m_stereoImage->height = m_leftImage->height;
                m_stereoImage->step   = m_leftImage->step;
            }
            // copy timestamp
            m_stereoImage->time = m_leftImage->time;

            // copy data from single images to stereo images
            memcpy(m_stereoImage->I1,m_leftImage->data,m_stereoImage->step*m_stereoImage->height*sizeof(unsigned char));
            memcpy(m_stereoImage->I2,m_rightImage->data,m_stereoImage->step*m_stereoImage->height*sizeof(unsigned char));

            // signal to main window that we have new data
            m_pickedNewStereo = false;
            emit DetectNewStereoImage();
            while (!m_pickedNewStereo )  usleep(1000);
        }
    }
}

void StereoImage::clear()
{
    m_kittiCapturedTime.clear();
    m_dadaoCapturedTime.clear();
    m_kittiPoses.clear();
    m_dadaoPoses.clear();
}
