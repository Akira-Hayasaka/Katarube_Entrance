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
#include "ofxXmlSettings.h"

class Kinect
{
public:
    
    void setup();
    void update();
    
    bool isInited();
    ofTexture& getDepthTexture() { return depthTex; }
    ofTexture& getThreshedTexture() { return threshedTex.getTexture(); }
    void drawContour(float x, float y, float w, float h);
    vector<ofPolyline> getContour() { return contourFinder.getPolylines(); }
    vector<ofPolyline> getWarpedContour(ofMatrix4x4 warpMat);
    
    void onAngleChanged(int& angle) { device.setCameraTiltAngle(angle); }
    void onNearThreshChanged(float& nearThresh) { this->nearThresh = nearThresh; }
    void onFarThreshChanged(float& farThresh) { this->farThresh = farThresh; }
    void onAngleAdjustChanged(float& angleAdjust) { this->angleAdjust = angleAdjust; }
    
    void onContourMinAreaChanged(float& contourMinArea) { this->contourMinArea = contourMinArea; }
    void onContourMaxAreaChanged(float& contourMaxArea) { this->contourMaxArea = contourMaxArea; }
    void onContourBriThreshChanged(float& contourBriThresh) { this->contourBriThresh = contourBriThresh; }
    void onFindContourHoleChanged(bool& bFindContourHole) { this->bFindContourHole = bFindContourHole; }
    
private:
    
    void storeDepthTex();
    void threshDepthTex();
    void makeContours();
    
    bool bKinectConnected;
    
    ofxKinect device;
    
    ofTexture depthTex;
    ofFbo threshedTex;
    ofShader depthThreshShader;
    float nearThresh;
    float farThresh;
    float angleAdjust;
    
    ofxCv::ContourFinder contourFinder;
    ofxCv::RectTracker contourTracker;
    ofPixels contourSourcePx;
    float contourMinArea;
    float contourMaxArea;
    float contourBriThresh;
    bool bFindContourHole;

    bool bInited;
    
    // debug
    ofVideoPlayer fakeKinect;
};

#endif /* Kinect_hpp */
