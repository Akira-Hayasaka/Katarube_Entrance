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
    ofAddListener(Global::updateHandPosEvent, this, &DrawingHand::onUpdateHandPos);
    ofAddListener(Global::handRetireEvent, this, &DrawingHand::onHandRetireEvent);
}

void DrawingHand::draw()
{
    bodyBase->draw(bodyState, bFromUpper, ang);
}

void DrawingHand::onTickEvent()
{
    if (bodyState.state != BodyState::NONE)
    {
        bodyState.curFrame++;
        if (bodyState.curFrame >= bodyBase->seq.size())
            bodyState.curFrame = 0;
        bodyState.blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        bodyBase->onTickEvent(bodyState);
    }
}

void DrawingHand::onDrawEvent(ofPoint dest)
{
    bFromUpper = false;//(ofRandomf() < 0.0) ? true : false;//(dest.y < APP_H/2) ? true : false;
    ang = ofRandom(-30, 30);
    
    bodyState.posOrig = ofPoint(dest.x, (bFromUpper) ? -500 : 1500, 0);
    bodyState.posDest = ofPoint(dest.x, dest.y, 0);
    bodyState.curPos = bodyState.posOrig;
    bodyState.curFrame = 0;
    Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posDest.y, 0.0f, 1.0f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &DrawingHand::onEndEmerge);
    bodyBase->genTweakTex(bodyState);
    bodyState.state = BodyState::EMERGE;
}

void DrawingHand::onUpdateHandPos(ofPoint& pos)
{
    bodyState.curPos = pos;
}

void DrawingHand::onHandRetireEvent()
{
    Tweenzor::add(&bodyState.curPos.y, bodyState.curPos.y, bodyState.posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&bodyState.curPos.y), this, &DrawingHand::onEndRetire);
    bodyState.state = BodyState::RETIRE;
}

void DrawingHand::onEndEmerge(float* arg)
{
    bodyState.state = BodyState::DOING;
    startDoingTime = Global::ELAPSED_TIME;
}

void DrawingHand::onEndRetire(float* arg)
{
    bodyState.state = BodyState::DONE;
}