//
//  PortraitTexture.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/9/16.
//
//

#include "PortraitTexture.hpp"

void PortraitTexture::setup(string path)
{
    ofLoadImage(*this, path);
}

void PortraitTexture::update()
{
    
}

void PortraitTexture::draw(float scaleF)
{
    ofVec2f rdmPos(cur.x + ofRandom(-5, 5), cur.y + ofRandom(-5, 5));
    ofVec2f rdmScale(scaleF * ofRandom(0.77, 0.8), scaleF * ofRandom(0.77, 0.8));
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(rdmPos);
    ofScale(rdmScale);
    ofRotateZ(ang);
    
    ofTexture::draw(0, 0);
    
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void PortraitTexture::doOnePlace(ofPoint cur)
{
    this->cur = cur;
}

void PortraitTexture::doHoriz(int idx,
                              ofPoint from, ofPoint to, ofPoint cur)
{
    this->idx = idx;
    this->ang = 0.0;
    this->from = from;
    this->to = to;
    this->cur = cur;
    bDone = false;
    
    float delay = idx * 0.7;
    Tweenzor::add(&this->cur.x, this->cur.x, this->to.x, delay, 10.0f, EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&this->cur.x), this, &PortraitTexture::onEndHoris);
}

void PortraitTexture::doVert(int idx, float ang,
                             ofPoint from, ofPoint to, ofPoint cur)
{
    this->idx = idx;
    this->ang = ang;
    this->from = from;
    this->to = to;
    this->cur = cur;
    bDone = false;
    
    float delay = idx * 0.5;
    float dur = 2;
    Tweenzor::add(&this->cur.y, this->cur.y, this->to.y, delay, dur, EASE_OUT_ELASTIC);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&this->cur.y), this, &PortraitTexture::onEndVertUp);
}

void PortraitTexture::onEndHoris(float* arg)
{
    bDone = true;
}

void PortraitTexture::onEndVertUp(float* arg)
{
    float delay = 0.0;
    float dur = 1.0;
    Tweenzor::add(&this->cur.y, this->cur.y, this->from.y, delay, dur, EASE_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&this->cur.y), this, &PortraitTexture::onEndVertDown);
}

void PortraitTexture::onEndVertDown(float* arg)
{
    bDone = true;
}