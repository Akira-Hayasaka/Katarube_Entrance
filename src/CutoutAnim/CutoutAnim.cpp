//
//  CutoutAnim.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#include "CutoutAnim.hpp"

void CutoutAnim::setup()
{
    cutoutFullScreen.allocate(APP_W, APP_H);
    blendCutout.load("shaders/common/simpleVert.vert", "shaders/scene/blendCutout.frag");
    
    knife.setup();
    portrait.setup();
    flyer.setup();
    
    ofAddListener(Global::tickEvent, this, &CutoutAnim::onTickEvent);
}

void CutoutAnim::update()
{
    knife.update();
    portrait.update();
    flyer.update();
}

void CutoutAnim::onTickEvent()
{
    cutoutFullScreen.begin();
    ofClear(255);
    blendCutout.begin();
    blendCutout.setUniformTexture("knife", knife.getTexture(), 0);
    blendCutout.setUniformTexture("portrait", portrait.getTexture(), 1);
    blendCutout.setUniformTexture("flyer", flyer.getTexture(), 2);
    blendCutout.setUniform3f("rdmForPortrait", ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05));
    blendCutout.setUniform3f("rdmForFlyer", ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05));
    drawPlane(cutoutFullScreen.getWidth(), cutoutFullScreen.getHeight());
    blendCutout.end();
    cutoutFullScreen.end();
}