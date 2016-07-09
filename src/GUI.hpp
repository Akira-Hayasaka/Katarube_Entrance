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
#include "Constants.h"
#include "Globals.hpp"
#include "Warper.hpp"

class GUI
{
public:
    
    void setup();
    void update();
    void draw();
    
    void toggleVisible() { bHide = !bHide; }
    void hide() { bHide = true; }
    void show() { bHide = false; }
    bool isVisible() { return !bHide; }
    
    void saveProjWarp();
    void saveKinectWarp();
    
private:
    
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
    bool bHide;
    
    // proj warp
    vector<Warper> projWarpers;
    
    // kinect warp
    Warper kinectWarper;
    ofFbo kinectFbo;
    vector<ofPolyline> contours;    
    vector<ofPath> contourPaths;    
};

#endif /* GUI_hpp */
