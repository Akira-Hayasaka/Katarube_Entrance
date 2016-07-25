//
//  Content.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#ifndef Content_hpp
#define Content_hpp

#include "ofMain.h"
#include "ofxCv.h"
#include "Body.hpp"
#include "Ink.hpp"
#include "CutoutAnim.hpp"
#include "Drawer.hpp"

class Content
{
public:
    
    void setup();
    void update();
    void genFullScreenContent();
    void drawLeft();
    void drawRight();
    void drawB2DEdge();
    void drawinteractionContours();
    ofTexture& getFullScreenTexture() { return fullScreenResult.getTexture(); }
    ofPolyline& getB2DEdge() { return b2dEdge; }
    
    void saveScreen();
    
private:
    
    void onTickEvent();
    void updateinteractionSource();
    
    ofFbo fullScreenResult;
    ofFbo outOfCanvasContent;
    ofFbo interactiveContent;
    ofFbo interactionSource;
    ofFbo bg;
    ofFbo bgMask;
    ofShader blendOutput;
    ofPolyline b2dEdge;
    vector<ofPolyline> interactionContours;
    vector<ofPtr<ofxBox2dPolygon> > interactionContourObjs;
    
    Body body;
    Ink ink;
    CutoutAnim cutout;
    Drawer drawer;
    
    ofxCv::ContourFinder contourFinder;
};

#endif /* Content_hpp */
