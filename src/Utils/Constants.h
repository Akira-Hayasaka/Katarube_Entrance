//
//  Constants.h
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#ifndef Constants_h
#define Constants_h

#include "ofMain.h"

static const int NUM_PROJ = 2;
static const int NUM_KINECT = 1;
static const float PROJ_W = 1920;
static const float PROJ_H = 1080;
static const float APP_W = PROJ_W * NUM_PROJ;
static const float APP_H = PROJ_H;
static const float KINECT_W = 640;
static const float KINECT_H = 480;
static const float KINECT_MAX_DIST = 400.0;
static const float KINECT_MIN_DIST = 80.0;
static const float WARP_TWEAK_SCALE = 0.2;

static const int CUTOFF_FPS = 12;

#endif /* Constants_h */
