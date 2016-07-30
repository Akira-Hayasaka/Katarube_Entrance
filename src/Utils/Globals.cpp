//
//  Globals.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#include "Globals.hpp"

namespace Globals
{
    float ELAPSED_TIME;
    float oneFrameDur;    
    float lastTickTime;
    long curTickFrame;
    
    string curAppState;
    
    Kinect kinect;
    vector<ofMatrix4x4> projMats;
    ofMatrix4x4 kinectMat;
    
    ofxBox2d* box2d;
    vector<ofPtr<ofxBox2dEdge> > box2dBBox;
    ofPolyline b2dEdge;
    vector<BottomLineAndAng> bottomLineAndAngs;
    
    ofVboMesh scrnQuad;
    
    ofPtr<UniformInfos> inkUniforms;
    
    vector<ofTexture> bodyBlendTexs;
    
    ofImage petip;
    
    KinectContourTransform leftKinectTrans;
    KinectContourTransform rightKinectTrans;
    
    // shaders
    ofShader chromaKey;
    ofShader whitize;
    ofShader completeWhite;
    ofShader strokeMask;
    
    // events
    ofEvent<void> tickEvent;
    
    ofEvent<void> beginLogoEvent;
    ofEvent<void> beginInfoEvent;
    ofEvent<void> fadeOutLogoEvent;
    ofEvent<void> fadeOutInfoEvent;
    ofEvent<void> fadeOutInkEvent;
    ofEvent<void> fadeOutCutoutEvent;
    ofEvent<void> fadeInCutoutEvent;
    ofEvent<void> putPuppetEvent;
    
    ofEvent<void> eatEvent;
    ofEvent<ofPoint> drawEvent;
    ofEvent<ofPoint> updateHandPosEvent;
    ofEvent<void> handRetireEvent;
    ofEvent<void> fetchEvent;
    ofEvent<ofPoint> putEvent;
    ofEvent<void> swipeEvent;
    
    ofEvent<DrawCommandInfo> genContourEvent;
    ofEvent<DrawCommandContour> gotContourEvent;
    ofEvent<DrawCommandContour> gotContourWHoleEvent;
    
    ofEvent<void> portraitOnePlaceEvent;
    ofEvent<void> portraitHorizEvent;
    ofEvent<void> portraitVertEvent;
    
    ofEvent<void> flyerFishLikeEvent;
    ofEvent<void> flyerWavyEvent;
    ofEvent<void> flyerStraightThingEvent;
    
    ofEvent<void> kyoEvent;
    
    ofEvent<void> knifeCircleEvent;
    ofEvent<void> knifeLineEvent;
    
    ofEvent<void> inkEvent;
    ofEvent<void> clearInkEvent;
}