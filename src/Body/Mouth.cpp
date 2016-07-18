//
//  Mouth.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Mouth.hpp"

void Mouth::setup(BodyBase* bodyBase)
{
    this->bodyBase = bodyBase;
    ofAddListener(Global::tickEvent, this, &Mouth::onTickEvent);
}

void Mouth::draw()
{
    bodyBase->draw(bodyState);
}

void Mouth::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        bodyState.blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (bodyState.state == BodyState::DOING)
        {
            if (bodyState.curFrame >= 26)
            {
                Tweenzor::add(&bodyState.curPos.x, bodyState.curPos.x, bodyState.posOrig.x, 0.0f, 0.6f, EASE_OUT_CUBIC);
                bodyState.state = BodyState::RETIRE;
            }
        }
        
        if (bodyState.curFrame >= bodyBase->seq.size())
        {
            bodyState.curFrame = 0;
            bodyState.state = BodyState::DONE;
        }
    }
}

void Mouth::onEatEvent()
{
    bodyState.posOrig = ofPoint(-700, 0, 0);
    bodyState.posDest = ofPoint::zero();
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.x, bodyState.curPos.x, bodyState.posDest.x, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.x), this, &Mouth::onEndEmerge);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void Mouth::onEndEmerge(float* arg)
{
    bodyState.state = BodyState::DOING;
}