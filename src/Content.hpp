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
#include "Mouth.hpp"
#include "Ink.hpp"
#include "CutoutAnim.hpp"

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
    
    bool bNeedTickUpdate;
    
    ofFbo fullScreenResult;
    ofFbo stopMotionContent;
    ofFbo bg;
    ofFbo bgMask;
    ofShader blendOutput;
    ofPolyline b2dEdge;
    
    Mouth mouth;
    Ink ink;
    
    CutoutAnim cutout;
};

#endif /* Content_hpp */
