//
//  Globals.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#ifndef Globals_hpp
#define Globals_hpp

#include "ofMain.h"
#include "Kinect.hpp"

namespace Global
{
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
}

#endif /* Globals_hpp */
