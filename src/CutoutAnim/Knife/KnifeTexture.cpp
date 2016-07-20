//
//  KnifeTexture.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/13/16.
//
//

#include "KnifeTexture.hpp"

void KnifeTexture::setup(int idx, int numkNives)
{
    this->idx = idx;
    this->numkNives = numkNives;
    state = NONE;
}

void KnifeTexture::update()
{
    setPosition(curPos);
}

void KnifeTexture::customDraw()
{
    if (Globals::ELAPSED_TIME - circBeginTime > circShowDelay * idx &&
        state == CIRC)
    {
        ofVec2f rdmPos(ofRandom(-5, 5), ofRandom(-5, 5));
        ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
        
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
        ofTranslate(rdmPos);
        ofScale(rdmScale);
        ofRotateZ(-ang);
        ofTexture::draw(0, 0);
        ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
}

void KnifeTexture::goCircle(ofPoint from, ofPoint interp, ofPoint to)
{
    state = CIRC;
    this->from = from;
    this->interp = interp;
    this->to = to;
    curPos = from;
    ofVec2f dv = to - from;
    ang = atan2(dv.x, dv.y) * 180 / PI;
    circBeginTime = Globals::ELAPSED_TIME;
    circShowDur = 0.25;
    circShowDelay = 0.1;
    float delay = circShowDelay * idx;
    Tweenzor::add(&curPos.x, curPos.x, interp.x, delay, circShowDur, EASE_OUT_CUBIC);
    Tweenzor::add(&curPos.y, curPos.y, interp.y, delay, circShowDur, EASE_OUT_CUBIC);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.x), this, &KnifeTexture::onEndInterp);
}

void KnifeTexture::goLine(ofPolyline motionLine)
{
    
}

void KnifeTexture::onEndInterp(float* arg)
{
    float delay = circShowDelay * numkNives - circShowDelay * idx;
    Tweenzor::add(&curPos.x, curPos.x, to.x, delay, 1.0f, EASE_IN_BACK);
    Tweenzor::add(&curPos.y, curPos.y, to.y, delay, 1.0f, EASE_IN_BACK);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.x), this, &KnifeTexture::onEndCircle);
}

void KnifeTexture::onEndCircle(float* arg)
{
    state = NONE;
}