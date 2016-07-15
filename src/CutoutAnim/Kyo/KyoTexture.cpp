//
//  KyoTexture.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/12/16.
//
//

#include "KyoTexture.hpp"

void KyoTexture::go()
{
    curScale = 0.0;
    curAlpha = 255.0;
    destScale = 0.7;
    destAlpha = 255.0;
    pos.set(ofRandom(300, APP_W - 300), ofRandom(200, APP_H - 200));

    vector<ofPoint> pts;
    for (auto p : Global::bottomLineAndAngs)
        pts.push_back(p.p);
    int nearestIdx = 0;
    getNearestPt(pts, pos, nearestIdx);
    ang = Global::bottomLineAndAngs.at(nearestIdx).ang;
    
    Tweenzor::add(&curAlpha, curAlpha, destAlpha, 0.0f, 1.0f, EASE_OUT_CIRC);
    Tweenzor::add(&curScale, curScale, destScale, 0.0f, 1.2f, EASE_OUT_BACK);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curScale), this, &KyoTexture::onEndIn);
    bRunning = true;
}

void KyoTexture::draw()
{
    if (bRunning)
    {
        ofVec2f rdmPos(ofRandom(-5, 5), ofRandom(-5, 5));
        ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
        
        ofPushStyle();
        ofSetColor(ofColor::white, curAlpha);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
        ofTranslate(pos + rdmPos);
        ofScale(curScale * rdmScale.x, curScale * rdmScale.y);
        ofRotateZ(ang);
        ofTexture::draw(0, 0);
        ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofPopStyle();
    }
}

void KyoTexture::onEndIn(float* arg)
{
    destScale = destScale + 0.5;
    destAlpha = 255.0;
    Tweenzor::add(&curAlpha, curAlpha, destAlpha, 0.0f, 0.5f, EASE_OUT_SINE);
    Tweenzor::add(&curScale, curScale, destScale, 0.0f, 0.5f, EASE_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curScale), this, &KyoTexture::onEndOut);
}

void KyoTexture::onEndOut(float* arg)
{
    bRunning = false;
}
