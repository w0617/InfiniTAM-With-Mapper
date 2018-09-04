CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
project(Mapper) # Your project name

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse4.2")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#=============================================InfiniTAM============================================
macro(CANONIFY_BOOL var)
  if (${var})
    set(${var} TRUE)
  else()
    set(${var} FALSE)
  endif()
endmacro()

find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(CUDA QUIET)
CANONIFY_BOOL(CUDA_FOUND)
message(STATUS "CUDA found: " ${CUDA_FOUND})

find_package(PNG QUIET)
CANONIFY_BOOL(PNG_FOUND)
message(STATUS "libpng found: ${PNG_FOUND}")

OPTION(WITH_CUDA "Build with CUDA support?" ${CUDA_FOUND})
INCLUDE(${PROJECT_SOURCE_DIR}/InfiniTAM/cmake/UseOpenMP.cmake)

OPTION(WITH_REALSENSE "Build with Intel RealSense support?" ${REALSENSE_FOUND})
OPTION(WITH_LIBROYALE "Build with LibRoyale support?" ${LibRoyale_FOUND})


add_subdirectory(InfiniTAM/ORUtils)
add_subdirectory(InfiniTAM/Utils)
add_subdirectory(InfiniTAM/Engine)
add_subdirectory(InfiniTAM/ITMLib)
add_subdirectory(InfiniTAM/Driver)

#=============================================InfiniTAM============================================

INCLUDE_DIRECTORIES(/usr/include/eigen3
                    /usr/local/include/pangolin
                    /usr/local/include
                    /usr/local/include/opencv
                    /usr/local/include/opencv2 
#                      /home/w/Desktop/SLAM/ORB_SLAM2/include 
                    ${PROJECT_SOURCE_DIR}/include )

LINK_DIRECTORIES( ${PROJECT_SOURCE_DIR}/lib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
#set(CMAKE_AUTOUIC ON)


# This will find the Qt5 files. You will need a QT5_DIR env variable
FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui QtXml QtOpenGL REQUIRED)
INCLUDE_DIRECTORIES( ${QT_INCLUDE_DIR} )


#opengl
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIR} )


set(SOURCES src/main.cpp
            src/mainwindow.cpp
            src/calibrationparameters.cpp
            src/stereoimage.cpp
            src/readlocalfilethread.cpp
            src/modelpainting.cpp
            Disparity/libelas/src/descriptor.cpp
            Disparity/libelas/src/elas.cpp
            libviso2/src/filter.cpp
            libviso2/src/matcher.cpp
            libviso2/src/matrix.cpp
            libviso2/src/triangle.cpp
            libviso2/src/viso.cpp
            libviso2/src/viso_stereo.cpp
            src/reconstructionthread.cpp
            src/getcameraposethread.cpp
            src/realtimecamthread.cpp
            src/infinitamthread.cpp
            Disparity/BM_SGBM/blockmatching.cpp
            Disparity/BM_SGBM/sgblockmatching.cpp
            Disparity/SPS_Stereo/SGMStereo.cpp
            Disparity/SPS_Stereo/SPSStereo.cpp )
 
set(HEADERS include/mainwindow.h
            include/calibrationparameters.h
            include/stereoimage.h
            include/readlocalfilethread.h
            include/modelpainting.h
            include/InfiniTAM.h
            Disparity/libelas/src/descriptor.h
            Disparity/libelas/src/elas.h
            libviso2/src/filter.h
            libviso2/src/matcher.h
            libviso2/src/matrix.h
            libviso2/src/timer.h
            libviso2/src/triangle.h
            libviso2/src/viso.h
            libviso2/src/viso_stereo.h
            include/reconstructionthread.h
            include/getcameraposethread.h
            include/realtimecamthread.h
            include/infinitamthread.h
            Disparity/BM_SGBM/blockmatching.h
            Disparity/BM_SGBM/sgblockmatching.h
            Disparity/SPS_Stereo/SGMStereo.h
            Disparity/SPS_Stereo/SPSStereo.h
            Disparity/SPS_Stereo/defParameter.h )

set(UI      ui/mainwindow.ui )

set(LIBRARIES  -lglut -lGLU
		/usr/local/lib/libopencv_calib3d.so
		/usr/local/lib/libopencv_highgui.so
		/usr/local/lib/libopencv_core.so
		/usr/local/lib/libopencv_imgproc.so
		/usr/local/lib/libopencv_imgcodecs.so
		-L"/usr/lib/x85_64-linux-gnu" -lexpat
		-lusb-1.0
# 		-L/home/w/Desktop/SLAM/ORB_SLAM2/lib -lORB_SLAM2
# 		-L/home/w/Desktop/SLAM/ORB_SLAM2/Thirdparty/g2o/lib -lg2o
# 		-L/home/w/Desktop/SLAM/ORB_SLAM2/Thirdparty/DBoW2/lib -lDBoW2
                -L/usr/local/lib -lpangolin )


find_package(CUDA QUIET)
CANONIFY_BOOL(CUDA_FOUND)
message(STATUS "Mapper CUDA found: " ${CUDA_FOUND})
OPTION(WITH_CUDA "Build with CUDA support?" ${CUDA_FOUND})
IF(WITH_CUDA)
  include_directories(${CUDA_INCLUDE_DIRS})
ELSE()
  add_definitions(-DCOMPILE_WITHOUT_CUDA)
ENDIF()



# This will create you executable
add_executable(Mapper ${SOURCES} ${HEADERS} ${UI})
# This will link necessary Qt5 libraries to your project
target_link_libraries(Mapper  ${LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY}
                              ${QT_QTXML_LIBRARY} ${QT_QTOPENGL_LIBRARY} ${OPENGL_LIBRARY}  )

target_link_libraries(Mapper Engine Utils ORUtils Driver)
