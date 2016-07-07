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
#include "CutoutAnim.hpp"

class Content
{
public:
    
    void setup();
    void update();
    void genFullScreenContent();
    void drawLeft();
    void drawRight();
    ofTexture& getFullScreenTexture() { return fullScreenResult.getTexture(); }
    
private:
    
    void onTickEvent();
    
    bool bNeedTickUpdate;
    
    ofFbo fullScreenResult;
    ofFbo stopMotionContent;
    ofFbo bg;
    ofFbo bgMask;
    ofShader blendOutput;
    
    Mouth mouth;
    
    CutoutAnim cutout;
};

#endif /* Content_hpp */
