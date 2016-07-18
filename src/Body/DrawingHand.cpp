//
//  DrawingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "DrawingHand.hpp"

void DrawingHand::setup(BodyBase* bodyBase)
{
    this->bodyBase = bodyBase;
    ofAddListener(Global::tickEvent, this, &DrawingHand::onTickEvent);
}

void DrawingHand::draw()
{
    bodyBase->draw(bodyState);
}

void DrawingHand::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        if (bodyState.curFrame >= bodyBase->seq.size())
            bodyState.curFrame = 0;
        bodyState.blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (bodyState.state == BodyState::DOING)
        {
            if (Global::ELAPSED_TIME - startDoingTime > doingDur)
            {
                Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &DrawingHand::onEndRetire);
                bodyState.state = BodyState::RETIRE;
            }
        }
    }
}

void DrawingHand::onDrawEvent()
{
    bodyState.posOrig = ofPoint(2200, 1500, 0);
    bodyState.posDest = ofPoint(2200, 100, 0);
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posDest.y, 0.0f, 1.0f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &DrawingHand::onEndEmerge);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void DrawingHand::onEndEmerge(float* arg)
{
    bodyState.state = BodyState::DOING;
    startDoingTime = Global::ELAPSED_TIME;
    doingDur = ofRandom(5.0, 10.0);
}

void DrawingHand::onEndRetire(float* arg)
{
    bodyState.state = BodyState::DONE;
}