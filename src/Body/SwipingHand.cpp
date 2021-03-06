//
//  SwipingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "SwipingHand.hpp"

void SwipingHand::setup(BodyBase* bodyBase)
{
    this->bodyBase = bodyBase;
    ofAddListener(Globals::tickEvent, this, &SwipingHand::onTickEvent);
}

void SwipingHand::draw()
{
    bodyBase->draw(bodyState);
}

void SwipingHand::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        if (bodyState.curFrame >= bodyBase->seq.size())
            bodyState.curFrame = 0;
        bodyState.blendIdx = ofRandom(Globals::bodyBlendTexs.size()-1);
        
        bodyBase->onTickEvent(bodyState);
    }
}

void SwipingHand::onSwipeEvent()
{
    bodyState.posOrig = ofPoint(-760, 0, 0);
    bodyState.posDest = ofPoint(APP_W, 0, 0);
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.x, bodyState.curPos.x, bodyState.posDest.x, 0.0f, 6.5f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.x), this, &SwipingHand::onEndSwipe);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void SwipingHand::onEndSwipe(float* arg)
{
    bodyState.state = BodyState::DONE;
}