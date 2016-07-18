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
#include "Mouth.hpp"
#include "DrawingHand.hpp"
#include "FetchingHand.hpp"
#include "PuttingHand.hpp"
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
    ofTexture& getFullScreenTexture() { return fullScreenResult.getTexture(); }
    ofPolyline& getB2DEdge() { return b2dEdge; }
    
    void saveScreen();
    
private:
    
    void onTickEvent();
    
    ofFbo fullScreenResult;
    ofFbo stopMotionContent;
    ofFbo bg;
    ofFbo bgMask;
    ofShader blendOutput;
    ofPolyline b2dEdge;
    
    Mouth mouth;
    DrawingHand drawingHand;
    FetchingHand fetchingHand;
    PuttingHand puttingHand;
    Ink ink;
    
    CutoutAnim cutout;
    
    Drawer drawer;
};

#endif /* Content_hpp */
