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
#include "ofxCv.h"
#include "ofxBox2d.h"
#include "Kinect.hpp"

enum APP_STATE
{
    NONE,
    DRAWING
};

namespace Global
{
    extern float ELAPSED_TIME;
    extern float lastTickTime;
    extern float oneFrameDur;
    
    extern APP_STATE appState;
    
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
    
    extern ofxBox2d box2d;
    
    extern ofVboMesh scrnQuad;
    
    extern ofxCv::ContourFinder drawingContourFinder;
    
    // shaders
    extern ofShader chromaKey;
    extern ofShader whitize;
    
    // events
    extern ofEvent<void> tickEvent;
    extern ofEvent<void> eatEvent;
    extern ofEvent<void> drawEvent;
}

#endif /* Globals_hpp */
