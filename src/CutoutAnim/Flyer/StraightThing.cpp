//
//  StraightThing.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#include "StraightThing.hpp"

void StraightThing::go()
{
    ofPoint from(0, APP_H/2 + ofRandom(-300, 300));
    ofPoint to(APP_W, APP_H/2 + ofRandom(-300, 300));
    
    if (ofRandomf() < 0.0)
    {
        ofPoint tmp = from;
        from = to;
        to = tmp;
        bLeftToRight = false;
    }
    else
        bLeftToRight = true;
    
    motionLine.clear();
    motionLine.addVertex(from);
    motionLine.addVertex(to);
    motionLine = motionLine.getResampledByCount(200);
    
    motionPct = 0.0;
    Tweenzor::add(&motionPct, motionPct, 1.0f, 0.0f, ofRandom(8, 12), EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&motionPct), this, &StraightThing::onEndMove);
    
    bMoving = true;
    setPosition(from);
}

void StraightThing::customDraw()
{
    ofVec2f rdmPos(ofRandom(-5, 5), ofRandom(-5, 5));
    ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
    
    ofPushMatrix();
    ofTranslate(rdmPos);
    ofScale(rdmScale);
    if (!bLeftToRight)
        ofRotateY(180);
    texs.at(texIdx).draw(0, 0);
    ofPopMatrix();
}