//
//  PuttingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "PuttingHand.hpp"

void PuttingHand::setup(string seqDirPath)
{
    BodyBase::setup(seqDirPath);
    ofAddListener(Global::putEvent, this, &PuttingHand::onPutEvent);
}

void PuttingHand::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        if (curFrame >= seq.size())
            curFrame = 0;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (state == DOING)
        {
            if (curFrame >= seq.size() * 0.5)
            {
                Tweenzor::add(&curPos.y, curPos.y, posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.y), this, &PuttingHand::onEndRetire);
                state = RETIRE;
            }
        }
        
        genTweakTex();
    }
}

void PuttingHand::onPutEvent()
{
    posOrig = ofPoint(2200, 1500, 0);
    posDest = ofPoint(2200, 100, 0);
    curPos = posOrig;
    curFrame = 0;
    Tweenzor::add(&curPos.y, curPos.y, posDest.y, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.y), this, &PuttingHand::onEndEmerge);
    genTweakTex();
    state = EMERGE;
}

void PuttingHand::onEndEmerge(float* arg)
{
    state = DOING;
}

void PuttingHand::onEndRetire(float* arg)
{
    state = NONE;
}