//
//  GUI.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#ifndef GUI_hpp
#define GUI_hpp

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxInkSim.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Warper.hpp"

class GUI
{
public:
    
    void setup(ofPtr<UniformInfos> kyoInkUniforms);
    void update();
    void draw();
    
    void toggleVisible() { bHide = !bHide; }
    void hide() { bHide = true; }
    void show() { bHide = false; }
    bool isVisible() { return !bHide; }
    
    void saveProjWarp();
    void saveKinectWarp();
    
private:
    
    void onleftKinectPosChangedX(float& arg);
    void onleftKinectPosChangedY(float& arg);
    void onleftKinectAngChanged(float& arg);
    void onleftKinectScaleChanged(float& arg);
    void onrightKinectPosChangedX(float& arg);
    void onrightKinectPosChangedY(float& arg);
    void onrightKinectAngChanged(float& arg);
    void onrightKinectScaleChanged(float& arg);
    
    // kinect device & contour
    ofxPanel kinectGUI;
    ofxIntSlider kinectAngle;
    ofxFloatSlider kinectNearThresh;
    ofxFloatSlider kinectFarThresh;
    ofxFloatSlider kinectAdjustAngle;
    ofxFloatSlider contourMinArea;
    ofxFloatSlider contourMaxArea;
    ofxFloatSlider contourThreshold;
    ofxToggle contourFindHole;
    ofxFloatSlider leftKinectPosX;
    ofxFloatSlider leftKinectPosY;
    ofxFloatSlider leftKinectAng;
    ofxFloatSlider leftKinectScale;
    ofxFloatSlider rightKinectPosX;
    ofxFloatSlider rightKinectPosY;
    ofxFloatSlider rightKinectAng;
    ofxFloatSlider rightKinectScale;
    bool bHide;
    
    // proj warp
    vector<Warper> projWarpers;
    
    // kinect warp
    Warper kinectWarper;
    ofFbo kinectFbo;
    vector<ofPolyline> contours;    
    vector<ofPath> contourPaths;
    
    // kyo ink
    ofxPanel kyoInkGui;
    ofPtr<UniformInfos> kyoInkUniforms;
};

#endif /* GUI_hpp */
