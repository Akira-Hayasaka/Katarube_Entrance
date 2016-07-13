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
#include "ofxInkSim.h"
#include "Kinect.hpp"

enum APP_STATE
{
    NONE,
    DRAWING
};

struct BottomLineAndAng
{
    ofPoint p;
    float ang;
};

namespace Global
{
    extern float ELAPSED_TIME;
    extern float oneFrameDur;    
    extern float lastTickTime;
    extern long curTickFrame;
    
    extern APP_STATE appState;
    
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
    
    extern ofxBox2d box2d;
    extern ofPolyline b2dEdge;
    extern vector<BottomLineAndAng> bottomLineAndAngs;
    
    extern ofVboMesh scrnQuad;
    
    extern ofxCv::ContourFinder globalContourFinder;
    
    extern ofPtr<UniformInfos> kyoInkUniforms;
    
    // shaders
    extern ofShader chromaKey;
    extern ofShader whitize;
    
    // events
    extern ofEvent<void> tickEvent;
    extern ofEvent<void> eatEvent;
    extern ofEvent<void> drawEvent;
    
    extern ofEvent<void> portraitOnePlaceEvent;
    extern ofEvent<void> portraitHorizEvent;
    extern ofEvent<void> portraitVertEvent;
    
    extern ofEvent<void> flyerFishLikeEvent;
    extern ofEvent<void> flyerWavyEvent;
    extern ofEvent<void> flyerStraightThingEvent;
    
    extern ofEvent<void> kyoEvent;
    
    extern ofEvent<void> inkEvent;
    extern ofEvent<void> clearInkEvent;
}

#endif /* Globals_hpp */
