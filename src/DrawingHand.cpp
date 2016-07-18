//
//  DrawingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "DrawingHand.hpp"

void DrawingHand::setup(string seqDirPath)
{
    BodyBase::setup(seqDirPath);
    ofAddListener(Global::drawEvent, this, &DrawingHand::onDrawEvent);
}

void DrawingHand::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        if (curFrame >= seq.size())
            curFrame = 0;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (state == DOING)
        {
            if (Global::ELAPSED_TIME - startDoingTime > doingDur)
            {
                Tweenzor::add(&curPos.y, curPos.y, posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.y), this, &DrawingHand::onEndRetire);
                state = RETIRE;
            }
        }
        
        genTweakTex();
    }
}

void DrawingHand::onDrawEvent()
{
    posOrig = ofPoint(2200, 1500, 0);
    posDest = ofPoint(2200, 100, 0);
    curPos = posOrig;
    curFrame = 0;
    Tweenzor::add(&curPos.y, curPos.y, posDest.y, 0.0f, 1.0f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.y), this, &DrawingHand::onEndEmerge);
    genTweakTex();
    state = EMERGE;
}

void DrawingHand::onEndEmerge(float* arg)
{
    state = DOING;
    startDoingTime = Global::ELAPSED_TIME;
    doingDur = ofRandom(5.0, 10.0);
}

void DrawingHand::onEndRetire(float* arg)
{
    state = NONE;
}