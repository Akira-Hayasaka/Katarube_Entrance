//
//  Kinect.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/16/16.
//
//

#ifndef Kinect_hpp
#define Kinect_hpp

#include "ofMain.h"
#include "Constants.h"
#include "ofxKinect.h"

class Kinect
{
public:
    
    void setup();
    void update();
    
    bool isInited() { return device.isInitialized() && device.isConnected() && bInited; }
    ofTexture& getDepthTexture() { return depthTex; }
    ofTexture& getThreshedTexture() { return threshedTex.getTexture(); }
    
    void onAngleChanged(int& angle) { device.setCameraTiltAngle(angle); }
    void onNearThreshChanged(float& nearThresh) { this->nearThresh = nearThresh; }
    void onFarThreshChanged(float& farThresh) { this->farThresh = farThresh; }
    
private:
    
    void storeDepthTex();
    void threshDepthTex();
    
    ofxKinect device;
    
    ofTexture depthTex;
    ofFbo threshedTex;
    ofShader depthThreshShader;
    float nearThresh;
    float farThresh;

    bool bInited;
};

#endif /* Kinect_hpp */
