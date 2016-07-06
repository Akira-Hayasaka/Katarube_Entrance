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
    extern float ELAPSED_TIME;
    extern float lastTickTime;
    extern float oneFrameDur;
    
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
    
    extern ofVboMesh scrnQuad;
    
    // shaders
    extern ofShader chromaKey;
    extern ofShader whitize;
    
    // events
    extern ofEvent<void> tickEvent;
    extern ofEvent<void> eatEvent;
}

#endif /* Globals_hpp */
