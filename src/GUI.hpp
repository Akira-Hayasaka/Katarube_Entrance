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

class GUI
{
public:
    
    void setup();
    void draw();
    
    void toggleVisible() { bHide = !bHide; }
    void hide() { bHide = true; }
    void show() { bHide = false; }
    
private:
    
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
};

#endif /* GUI_hpp */
