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
    kyo.setup();
    
    alpha = 0.0;
    
    ofAddListener(Globals::tickEvent, this, &CutoutAnim::onTickEvent);
    ofAddListener(Globals::fadeOutCutoutEvent, this, &CutoutAnim::onFadeOut);
    ofAddListener(Globals::fadeInCutoutEvent, this, &CutoutAnim::onFadeIn);
}

void CutoutAnim::update()
{
    knife.update();
    portrait.update();
    flyer.update();
    kyo.update();
}

void CutoutAnim::onTickEvent()
{
    cutoutFullScreen.begin();
    ofClear(255);
    blendCutout.begin();
    blendCutout.setUniformTexture("knife", knife.getTexture(), 0);
    blendCutout.setUniformTexture("portrait", portrait.getTexture(), 1);
    blendCutout.setUniformTexture("flyer", flyer.getTexture(), 2);
    blendCutout.setUniformTexture("kyo", kyo.getTexture(), 3);
    blendCutout.setUniform3f("rdmForPortrait", ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05), ofRandom(-0.05, 0.05));
    blendCutout.setUniform3f("rdmForFlyer", ofRandom(-0.025, 0.025), ofRandom(-0.025, 0.025), ofRandom(-0.025, 0.025));
    blendCutout.setUniform3f("rdmForKyo", ofRandom(-0.025, 0.025), ofRandom(-0.025, 0.025), ofRandom(-0.025, 0.025));
    drawPlane(cutoutFullScreen.getWidth(), cutoutFullScreen.getHeight());
    blendCutout.end();
    
    ofPushStyle();
    ofSetColor(ofColor::white, alpha);
    ofDrawRectangle(0, 0, cutoutFullScreen.getWidth(), cutoutFullScreen.getHeight());
    ofPopStyle();
    
    cutoutFullScreen.end();
}

void CutoutAnim::onFadeOut()
{
    Tweenzor::add(&alpha, alpha, 255.0f, 0.0f, 1.0f, EASE_OUT_SINE);
}

void CutoutAnim::onFadeIn()
{
    Tweenzor::add(&alpha, alpha, 0.0f, 0.0f, 1.0f, EASE_OUT_SINE);
}