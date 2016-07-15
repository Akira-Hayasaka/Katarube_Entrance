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
    
    ofxCv::ContourFinder globalContourFinder;
    
    ofPtr<UniformInfos> inkUniforms;
    
    // shaders
    ofShader chromaKey;
    ofShader whitize;
    
    // events
    ofEvent<void> tickEvent;
    ofEvent<void> eatEvent;
    ofEvent<void> drawEvent;
    
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