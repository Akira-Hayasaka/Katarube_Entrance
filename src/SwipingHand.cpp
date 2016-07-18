//
//  SwipingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "SwipingHand.hpp"

void SwipingHand::setup(string seqDirPath)
{
    BodyBase::setup(seqDirPath);
    ofAddListener(Global::swipeEvent, this, &SwipingHand::onSwipeEvent);
}

void SwipingHand::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        if (curFrame >= seq.size())
            curFrame = 0;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        genTweakTex();
    }
}

void SwipingHand::onSwipeEvent()
{
    posOrig = ofPoint(-760, 0, 0);
    posDest = ofPoint(APP_W, 0, 0);
    curPos = posOrig;
    curFrame = 0;
    Tweenzor::add(&curPos.x, curPos.x, posDest.x, 0.0f, 2.0f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.x), this, &SwipingHand::onEndSwipe);
    genTweakTex();
    state = EMERGE;
}

void SwipingHand::onEndSwipe(float* arg)
{
    state = NONE;
}