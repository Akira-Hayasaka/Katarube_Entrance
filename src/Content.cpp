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
    
//    ofTexture bgRight;
//    ofTexture bgMaskRight;
//    ofTexture bgLeft;
//    ofTexture bgMaskLeft;
//    ofLoadImage(bgLeft, "imgs/common/bg_left.png");
//    ofLoadImage(bgMaskLeft, "imgs/common/bgMask_left.png");
//    ofLoadImage(bgRight, "imgs/common/bg_right.png");
//    ofLoadImage(bgMaskRight, "imgs/common/bgMask_right.png");
    
    ofTexture bg_s;
    ofTexture bgMask_s;
    ofLoadImage(bg_s, "imgs/common/bg_2.png");
    ofLoadImage(bgMask_s, "imgs/common/bgMask_2.png");
    
    bg.begin();
    ofClear(0);
    bg_s.draw(0, 0);
    bg.end();
    
    bgMask.begin();
    ofClear(0);
    bgMask_s.draw(0, 0);
    bgMask.end();
    
    mouth.setup("imgs/seq/mouth/1", "imgs/seqBlendTex");
    
    cutout.setup();
    
    bNeedTickUpdate = false;
    
    ofAddListener(Global::tickEvent, this, &Content::onTickEvent);
}

void Content::update()
{
    mouth.update();
    cutout.update();
    
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
    blendOutput.setUniformTexture("cutout", cutout.getTexture(), 1);
    blendOutput.setUniformTexture("bg", bg.getTexture(), 2);
    blendOutput.setUniformTexture("bgMask", bgMask.getTexture(), 3);
    drawPlane(APP_W, APP_H);
    blendOutput.end();
    
//    if (Global::ELAPSED_TIME - Global::lastTickTime < 0.04)
//    {
//        ofPushStyle();
//        ofSetColor(ofColor::gray, 5);
//        bgMask.draw(0, 0);
//        ofPopStyle();
//    }
    
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

void Content::saveScreen()
{
    fullScreenResult.begin();
    ofClear(0);
    bg.draw(0, 0);
    fullScreenResult.end();
    
    ofPixels px;
    fullScreenResult.readToPixels(px);
    ofSaveImage(px, "imgs/saved/bg.png");
    
    fullScreenResult.begin();
    ofClear(0);
    bgMask.draw(0, 0);
    fullScreenResult.end();
    
    fullScreenResult.readToPixels(px);
    ofSaveImage(px, "imgs/saved/bgMask.png");
}