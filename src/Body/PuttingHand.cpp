//
//  PuttingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "PuttingHand.hpp"

void PuttingHand::setup(BodyBase* bodyBase)
{
    this->bodyBase = bodyBase;
    ofAddListener(Global::tickEvent, this, &PuttingHand::onTickEvent);
}

void PuttingHand::draw()
{
    bodyBase->draw(bodyState, false, ang);
}

void PuttingHand::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        if (bodyState.curFrame >= bodyBase->seq.size())
            bodyState.curFrame = 0;
        bodyState.blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (bodyState.state == BodyState::DOING)
        {
            if (bodyState.curFrame >= bodyBase->seq.size() * 0.5)
            {
                Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &PuttingHand::onEndRetire);
                bodyState.state = BodyState::RETIRE;
            }
        }
        
        bodyBase->onTickEvent(bodyState);
    }
}

void PuttingHand::onPutEvent(ofPoint dest)
{
    ang = ofRandom(-10, 10);
    
    bodyState.posOrig = ofPoint(dest.x, 1500, 0);
    bodyState.posDest = dest;
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posDest.y, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &PuttingHand::onEndEmerge);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void PuttingHand::onEndEmerge(float* arg)
{
    bodyState.state = BodyState::DOING;
}

void PuttingHand::onEndRetire(float* arg)
{
    bodyState.state = BodyState::DONE;
}