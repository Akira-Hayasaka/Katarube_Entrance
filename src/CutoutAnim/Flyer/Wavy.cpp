//
//  Wavy.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#include "Wavy.hpp"

void Wavy::go()
{
    ofPoint from(ofRandom(300, APP_W - 300), APP_H);
    ofPoint to(from.x + ofRandom(-200, 200), -100);
    motionLine.clear();
    motionLine.addVertex(from);
    motionLine.addVertex(to);
    motionLine = motionLine.getResampledByCount(200);
    
    motionPct = 0.0;
    Tweenzor::add(&motionPct, motionPct, 1.0f, 0.0f, ofRandom(8, 12), EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&motionPct), this, &Wavy::onEndMove);
    
    bMoving = true;
    setPosition(from);
}

void Wavy::customDraw()
{
    ofVec2f rdmPos(ofRandom(-5, 5), ofRandom(-5, 5));
    ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
    
    ofPushMatrix();
    ofTranslate(rdmPos);
    ofScale(rdmScale);
    texs.at(texIdx).draw(0, 0);
    ofPopMatrix();
}