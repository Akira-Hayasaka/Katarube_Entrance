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
#include "ofxBox2d.h"
#include "ofxInkSim.h"
#include "Kinect.hpp"

struct BottomLineAndAng
{
    ofPoint p;
    float ang;
};

struct DrawCommandInfo
{
    string cmdID;
    ofPixels px;
    float contourMinArea;
    float contourMaxArea;
    float contourBriThresh;
};

struct DrawCommandContour
{
    string cmdID;
    vector<ofPolyline> contours;
};

namespace Global
{
    extern float ELAPSED_TIME;
    extern float oneFrameDur;    
    extern float lastTickTime;
    extern long curTickFrame;
    
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
    
    extern ofxBox2d box2d;
    extern ofPolyline b2dEdge;
    extern vector<BottomLineAndAng> bottomLineAndAngs;
    
    extern ofVboMesh scrnQuad;
    
    extern ofPtr<UniformInfos> inkUniforms;
    
    extern vector<ofTexture> bodyBlendTexs;
    
    extern ofTexture petip;
    
    // shaders
    extern ofShader chromaKey;
    extern ofShader whitize;
    extern ofShader strokeMask;    
    
    // events
    extern ofEvent<void> tickEvent;
    
    extern ofEvent<void> beginLogoEvent;
    extern ofEvent<void> beginInfoEvent;
    
    extern ofEvent<void> eatEvent;
    extern ofEvent<ofPoint> drawEvent;
    extern ofEvent<ofPoint> updateHandPosEvent;
    extern ofEvent<void> handRetireEvent;
    extern ofEvent<void> fetchEvent;
    extern ofEvent<void> putEvent;
    extern ofEvent<void> swipeEvent;
    
    extern ofEvent<DrawCommandInfo> genContourEvent;
    extern ofEvent<DrawCommandContour> gotContourEvent;
    extern ofEvent<DrawCommandContour> gotContourWHoleEvent;
    
    extern ofEvent<void> portraitOnePlaceEvent;
    extern ofEvent<void> portraitHorizEvent;
    extern ofEvent<void> portraitVertEvent;
    
    extern ofEvent<void> flyerFishLikeEvent;
    extern ofEvent<void> flyerWavyEvent;
    extern ofEvent<void> flyerStraightThingEvent;
    
    extern ofEvent<void> kyoEvent;
    
    extern ofEvent<void> knifeCircleEvent;
    extern ofEvent<void> knifeLineEvent;
    
    extern ofEvent<void> inkEvent;
    extern ofEvent<void> clearInkEvent;
}

#endif /* Globals_hpp */
