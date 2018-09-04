#ifndef RECONSTRUCTION_H
#define RECONSTRUCTION_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <time.h>

#include "include/calibrationparameters.h"
#include "include/stereoimage.h"
#include "include/modelpainting.h"
#include "include/readlocalfilethread.h"

#include "Disparity/libelas/src/elas.h"
#include "Disparity/BM_SGBM/blockmatching.h"
#include "Disparity/BM_SGBM/sgblockmatching.h"
#include "Disparity/SPS_Stereo/SPSStereo.h"

class ReconstructionThread : public QThread
{
    Q_OBJECT

public:

    ReconstructionThread(CalibrationParameters *calib, StereoImage *stereo, QObject *parent = 0);
    ~ReconstructionThread();

    //Send image and pose from the mainwindow thread to this vo thread.
    void SendImageAndPose(StereoImage::StereoImageParameters &s, libviso2_Matrix H);

    //The funtion for the mainwindow to get the 3d map points and the homographylibviso2_Matrix
    std::vector<ModelPainting::Point3D> GetMapPoints (){return m_mapPoints;}
    libviso2_Matrix GetHomographyTotal() { return m_HomographyMatrix; }

    void PickupNewMap() { m_pickedNewMap = true; }

    void bm_arrayToMat(uchar* arr, cv::Mat &image)
    {
        for(int i=0; i<m_stereoImage->height; i++)
            for(int j=0; j<m_stereoImage->step; j++)
            { image.at<uchar>(i,j) = *arr, arr++; }
    }

    void bm_matToArray(cv::Mat image, float* arr)
    {
        for(int i=0; i<m_stereoImage->height; i++)
            for(int j=0; j<m_stereoImage->width; j++)
            { *arr = image.at<float>(i,j); arr++; }
    }

    void sps_arrayToPng(uchar* arr, png::image<png::rgb_pixel> &imagePng)
    {
        for(int i=0; i<m_stereoImage->height; i++)
            for(int j=0; j<m_stereoImage->step; j++)
            {
                png::rgb_pixel rgbPixel(*arr, *arr, *arr);
                imagePng.set_pixel(j, i, rgbPixel);
                arr++;
            }
    }

    void sps_pngToArrary(png::image<png::gray_pixel_16> &imagePng, float* arr)
    {
        for(int i=0; i<m_stereoImage->height; i++)
            for(int j=0; j<m_stereoImage->width; j++)
            {   *arr = (imagePng.get_pixel(j, i) / 256.0); arr++;  }
    }

    BlockMatching bm;
    SGBlockMatching sgbm;
    SPSStereo sps;

protected:

    void run();

private:

    //structruer: Map
    struct Map3d
    {
        float*   I;      // image
        float*   D;      // disparity map
        float*   X;      // 3d coordinates
        float*   Y;
        float*   Z;
        libviso2_Matrix   H;      // extrinsics
        int32_t  width;  // image dimensions
        int32_t  height;
        int32_t  idx;    // index in point list

        Map3d()
        {
            I = 0;
            D = 0;
            X = 0;
            Y = 0;
            Z = 0;

            H = libviso2_Matrix();
            width = 0;
            height = 0;
            idx = 0;
        }

        ~Map3d()
        {
            // Release the memory.
            if(I != 0)
            {
                free(I);
                I = 0;
            }
            if(D != 0)
            {
                free(D);
                D = 0;
            }
            if(X != 0)
            {
                free(X);
                X = 0;
            }
            if(Y != 0)
            {
                free(Y);
                Y = 0;
            }
            if(Z != 0)
            {
                free(Z);
                Z = 0;
            }

            H = libviso2_Matrix();
            width = 0;
            height = 0;
            idx = 0;

        }

        inline Map3d& operator=(const Map3d& map)
        {
            if(height != map.height || width != map.width)
            {
                // Release the memory.
                if(I != 0)
                {
                    free(I);
                    I = 0;
                }
                if(D != 0)
                {
                    free(D);
                    D = 0;
                }
                if(X != 0)
                {
                    free(X);
                    X = 0;
                }
                if(Y != 0)
                {
                    free(Y);
                    Y = 0;
                }
                if(Z != 0)
                {
                    free(Z);
                    Z = 0;
                }

                // Alloc the memory
                I      = (float*)malloc(map.width * map.height * sizeof(float));
                D      = (float*)malloc(map.width * map.height * sizeof(float));
                X      = (float*)malloc(map.width * map.height * sizeof(float));
                Y      = (float*)malloc(map.width * map.height * sizeof(float));
                Z      = (float*)malloc(map.width * map.height * sizeof(float));
            }

            // Copy
            memcpy(I, map.I ,map.width * map.height * sizeof(float));
            memcpy(D, map.D ,map.width * map.height * sizeof(float));
            memcpy(X, map.X ,map.width * map.height * sizeof(float));
            memcpy(Y, map.Y ,map.width * map.height * sizeof(float));
            memcpy(Z, map.Z ,map.width * map.height * sizeof(float));
            H = map.H;
            width = map.width;
            height = map.height;
            idx = map.idx;

            return *this;
        }
    };

    Map3d CreateCurrentMap();
    void  AddDisparityMapToReconstruction();
    void  ReleaseMap(Map3d& m);

    CalibrationParameters *m_calib;
    StereoImage *m_stereo;
    StereoImage::StereoImageParameters *m_stereoImage;


    std::vector<ModelPainting::Point3D> m_mapPoints;

    bool m_pickedNewMap;
    float m_showingMinDistance;
    float m_showingMaxDistance;

    libviso2_Matrix m_HomographyMatrix;

    double m_f; // x focal length in pixels.
    double m_cu; // principal point (u-coordinate) in pixels
    double m_cv; // principal point (v-coordinate) in pixels
    double m_baseline;// baseline in meters

signals:

    void DetectNewMap();

public slots:

};

#endif // RECONSTRUCTION_H
