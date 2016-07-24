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

namespace Globals
{
    extern float ELAPSED_TIME;
    extern float oneFrameDur;    
    extern float lastTickTime;
    extern long curTickFrame;
    
    extern string curAppState;
    
    extern Kinect kinect;
    extern vector<ofMatrix4x4> projMats;
    extern ofMatrix4x4 kinectMat;
    
    extern ofxBox2d box2d;
    extern vector<ofPtr<ofxBox2dEdge> > box2dBBox;
    extern ofPolyline b2dEdge;
    extern vector<BottomLineAndAng> bottomLineAndAngs;
    
    extern ofVboMesh scrnQuad;
    
    extern ofPtr<UniformInfos> inkUniforms;
    
    extern vector<ofTexture> bodyBlendTexs;
    
    extern ofImage petip;
    
    // shaders
    extern ofShader chromaKey;
    extern ofShader whitize;
    extern ofShader strokeMask;    
    
    // events
    extern ofEvent<void> tickEvent;
    
    extern ofEvent<void> beginLogoEvent;
    extern ofEvent<void> beginInfoEvent;
    extern ofEvent<void> fadeOutLogoEvent;
    extern ofEvent<void> fadeOutInfoEvent;
    extern ofEvent<void> fadeOutInkEvent;
    extern ofEvent<void> fadeOutCutoutEvent;
    extern ofEvent<void> fadeInCutoutEvent;
    extern ofEvent<void> putPuppetEvent;
    
    extern ofEvent<void> eatEvent;
    extern ofEvent<ofPoint> drawEvent;
    extern ofEvent<ofPoint> updateHandPosEvent;
    extern ofEvent<void> handRetireEvent;
    extern ofEvent<void> fetchEvent;
    extern ofEvent<ofPoint> putEvent;
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
