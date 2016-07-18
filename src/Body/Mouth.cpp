//
//  Mouth.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Mouth.hpp"

void Mouth::setup(string seqDirPath)
{
    BodyBase::setup(seqDirPath);
    ofAddListener(Global::eatEvent, this, &Mouth::onEatEvent);
}

void Mouth::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        
        if (state == DOING)
        {
            if (curFrame >= 26)
            {
                Tweenzor::add(&curPos.x, curPos.x, posOrig.x, 0.0f, 0.6f, EASE_OUT_CUBIC);
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

void Mouth::onEatEvent()
{
    posOrig = ofPoint(-700, 0, 0);
    posDest = ofPoint::zero();
    curPos = posOrig;
    curFrame = 0;
    Tweenzor::add(&curPos.x, curPos.x, posDest.x, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curPos.x), this, &Mouth::onEndEmerge);
    genTweakTex();
    state = EMERGE;
}

void Mouth::onEndEmerge(float* arg)
{
    state = DOING;
}