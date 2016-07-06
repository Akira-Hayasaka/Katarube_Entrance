//
//  Content.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Content.hpp"

void Content::setup()
{
    fullScreenResult.allocate(APP_W, APP_H);
    stopMotionContent.allocate(APP_W, APP_H);
    bg.allocate(APP_W, APP_H);
    bgMask.allocate(APP_W, APP_H);
    blendOutput.load("shaders/common/simpleVert.vert", "shaders/scene/blendOutput.frag");
    
    ofTexture bgRight;
    ofTexture bgMaskRight;
    ofTexture bgLeft;
    ofTexture bgMaskLeft;
    ofLoadImage(bgLeft, "imgs/common/bg_left.png");
    ofLoadImage(bgMaskLeft, "imgs/common/bgMask_left.png");
    ofLoadImage(bgRight, "imgs/common/bg_right.png");
    ofLoadImage(bgMaskRight, "imgs/common/bgMask_right.png");
    
    bg.begin();
    ofClear(0);
    bgLeft.draw(0, 0);
    bgRight.draw(PROJ_W, 0);
    bg.end();
    
    bgMask.begin();
    ofClear(0);
    bgMaskLeft.draw(0, 0);
    bgMaskRight.draw(PROJ_W, 0);
    bgMask.end();
    
    mouth.setup("imgs/seq/mouth/1", "imgs/seqBlendTex");
    
    bNeedTickUpdate = false;
    
    ofAddListener(Global::tickEvent, this, &Content::onTickEvent);
}

void Content::update()
{
    mouth.update();
    
    if (bNeedTickUpdate)
    {
        // draw every stop motion content here
        stopMotionContent.begin();
        ofClear(0);
        mouth.draw();
        stopMotionContent.end();
        
        bNeedTickUpdate = false;
    }
}

void Content::genFullScreenContent()
{
    fullScreenResult.begin();
    ofClear(0);
    
    blendOutput.begin();
    blendOutput.setUniformTexture("content", stopMotionContent.getTexture(), 0);
    blendOutput.setUniformTexture("bg", bg.getTexture(), 1);
    blendOutput.setUniformTexture("bgMask", bgMask.getTexture(), 2);
    drawPlane(APP_W, APP_H);
    blendOutput.end();
    
    if (Global::ELAPSED_TIME - Global::lastTickTime < 0.04)
    {
        ofPushStyle();
        ofSetColor(ofColor::gray, 5);
        bgMask.draw(0, 0);
        ofPopStyle();
    }
    
    fullScreenResult.end();
}

void Content::drawLeft()
{
    fullScreenResult.getTexture().drawSubsection(0, 0, PROJ_W, PROJ_H, 0, 0);
}

void Content::drawRight()
{
    fullScreenResult.getTexture().drawSubsection(PROJ_W, 0, PROJ_W, PROJ_H, PROJ_W, 0);
}

void Content::onTickEvent()
{
    bNeedTickUpdate = true;
}
