//
//  Globals.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#include "Globals.hpp"

namespace Global
{
    float ELAPSED_TIME;
    float oneFrameDur;    
    float lastTickTime;
    long curTickFrame;
    
    Kinect kinect;
    vector<ofMatrix4x4> projMats;
    ofMatrix4x4 kinectMat;
    
    ofxBox2d box2d;
    ofPolyline b2dEdge;
    vector<BottomLineAndAng> bottomLineAndAngs;
    
    ofVboMesh scrnQuad;
    
    ofPtr<UniformInfos> inkUniforms;
    
    vector<ofTexture> bodyBlendTexs;
    
    ofTexture petip;
    
    // shaders
    ofShader chromaKey;
    ofShader whitize;
    ofShader strokeMask;
    
    // events
    ofEvent<void> tickEvent;
    
    ofEvent<void> beginLogoEvent;
    ofEvent<void> beginInfoEvent;
    
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