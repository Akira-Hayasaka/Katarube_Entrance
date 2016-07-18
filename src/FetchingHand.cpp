//
//  FetchingHand.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "FetchingHand.hpp"

void FetchingHand::setup(string seqDirPath)
{
    BodyBase::setup(seqDirPath);
    ofAddListener(Global::fetchEvent, this, &FetchingHand::onFetchEvent);
}

void FetchingHand::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (state == DOING)
        {
            if (curFrame >= 18)
            {
                Tweenzor::add(&curPos.y, curPos.y, posOrig.y, 0.0f, 0.6f, EASE_OUT_CUBIC);
                state = RETIRE;
            }
        }
        
        if (curFrame >= seq.size())
        {
            curFrame = 0;
            state = NONE;
        }
        
        genTweakTex();
    }
}

void FetchingHand::onFetchEvent()
{
    posOrig = ofPoint(2200, 1500, 0);
    posDest = ofPoint(2200, 100, 0);
    curPos = posOrig;
    curFrame = 0;
    Tweenzor::add(&curPos.y, curPos.y, posDest.y, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.y), this, &FetchingHand::onEndEmerge);
    genTweakTex();
    state = EMERGE;
}

void FetchingHand::onEndEmerge(float* arg)
{
    state = DOING;
}
