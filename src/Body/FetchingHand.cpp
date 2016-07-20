//
//  FetchingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "FetchingHand.hpp"

void FetchingHand::setup(BodyBase* bodyBase)
{
    this->bodyBase = bodyBase;
    ofAddListener(Globals::tickEvent, this, &FetchingHand::onTickEvent);
}

void FetchingHand::draw()
{
    bodyBase->draw(bodyState);
}

void FetchingHand::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        bodyState.blendIdx = ofRandom(Globals::bodyBlendTexs.size()-1);
        
        if (bodyState.state == BodyState::DOING)
        {
            if (bodyState.curFrame >= 18)
            {
                Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                bodyState.state = BodyState::RETIRE;
            }
        }
        
        if (bodyState.curFrame >= bodyBase->seq.size())
        {
            bodyState.curFrame = 0;
            bodyState.state = BodyState::DONE;
        }
        
        bodyBase->onTickEvent(bodyState);
    }
}

void FetchingHand::onFetchEvent()
{
    bodyState.posOrig = ofPoint(2200, 1500, 0);
    bodyState.posDest = ofPoint(2200, 100, 0);
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posDest.y, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &FetchingHand::onEndEmerge);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void FetchingHand::onEndEmerge(float* arg)
{
    bodyState.state = BodyState::DOING;
}
