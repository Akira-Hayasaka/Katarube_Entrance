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
#include "ofxCv.h"
#include "ofxKinect.h"

class Kinect
{
public:
    
    void setup();
    void update();
    
    bool isInited() { return device.isInitialized() && device.isConnected() && bInited; }
    ofTexture& getDepthTexture() { return depthTex; }
    ofTexture& getThreshedTexture() { return threshedTex.getTexture(); }
    void drawContour();
    
    void onAngleChanged(int& angle) { device.setCameraTiltAngle(angle); }
    void onNearThreshChanged(float& nearThresh) { this->nearThresh = nearThresh; }
    void onFarThreshChanged(float& farThresh) { this->farThresh = farThresh; }
    
    void onContourMinAreaChanged(float& contourMinArea) { this->contourMinArea = contourMinArea; }
    void onContourMaxAreaChanged(float& contourMaxArea) { this->contourMaxArea = contourMaxArea; }
    void onContourBriThreshChanged(float& contourBriThresh) { this->contourBriThresh = contourBriThresh; }
    void onFindContourHoleChanged(bool& bFindContourHole) { this->bFindContourHole = bFindContourHole; }
    
private:
    
    void storeDepthTex();
    void threshDepthTex();
    void makeContours();
    
    ofxKinect device;
    
    ofTexture depthTex;
    ofFbo threshedTex;
    ofShader depthThreshShader;
    float nearThresh;
    float farThresh;
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::RectTracker contourTracker;
    ofPixels contourSourcePx;
    float contourMinArea;
    float contourMaxArea;
    float contourBriThresh;
    bool bFindContourHole;

    bool bInited;
};

#endif /* Kinect_hpp */