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
    float lastTickTime;
    float oneFrameDur;
    
    Kinect kinect;
    vector<ofMatrix4x4> projMats;
    ofMatrix4x4 kinectMat;
    
    ofVboMesh scrnQuad;
    
    // shaders
    ofShader chromaKey;
    ofShader whitize;
    
    // events
    ofEvent<void> tickEvent;
    ofEvent<void> eatEvent;
}