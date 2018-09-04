#ifndef INFINITAM_H
#define INFINITAM_H

#include "InfiniTAM/Engine/ImageSourceEngine.h"
#include "InfiniTAM/ITMLib/Engine/ITMMainEngine.h"

using namespace InfiniTAM::Engine;


static ImageSourceEngine *imageSource = NULL;
static ITMLibSettings *internalSettings = NULL;
static ITMMainEngine *mainEngine = NULL;

static bool disparityFromFile = false;

#endif
