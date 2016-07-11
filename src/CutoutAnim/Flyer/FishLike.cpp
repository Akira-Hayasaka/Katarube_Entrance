//
//  FishLike.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#include "FishLike.hpp"

void FishLike::go()
{
    ofPoint from(ofRandom(500, APP_W - 500), 0);
    ofPoint p1, p2, p3;
    ofVec2f cp11, cp12, cp21, cp22, cp31, cp32;

    float width = ofRandom(1500, 2000);
    float height = ofRandom(400, 700);
    float open = ofRandom(-500, -700);
    
    if (from.x < APP_W/2)
    {
        p1.set(from.x - open, from.y + height);
        p2.set(p1.x + width, p1.y);
        p3.set(p2.x - open, from.y);
        leftToRight = true;
    }
    else
    {
        p1.set(from.x + open, from.y + height);
        p2.set(p1.x - width, p1.y);
        p3.set(p2.x + open, from.y);
        leftToRight = false;
    }
    
    ofPolyline tmp;
    ofPoint centroid;
    ofVec2f mid;
    float dist;
    
    tmp.addVertex(from);
    tmp.addVertex(p1);
    tmp.addVertex(p2);
    tmp.addVertex(p3);
    tmp.setClosed(true);
    centroid = tmp.getCentroid2D();
    
    mid = from.getMiddle(p1);
    dist = mid.distance(centroid);
    cp11 = mid + (mid - centroid).getNormalized() * ofRandom(50, 150);
    cp12 = cp11;
    
    mid = p1.getMiddle(p2);
    dist = mid.distance(centroid);
    cp21 = mid + (mid - centroid).getNormalized() * ofRandom(350, 450);
    cp22 = cp21;
    
    mid = p2.getMiddle(p3);
    dist = mid.distance(centroid);
    cp31 = mid + (mid - centroid).getNormalized() * ofRandom(50, 150);
    cp32 = cp31;

    motionLine.clear();
    motionLine.addVertex(from);
    motionLine.bezierTo(cp11, cp12, p1, 100);
    motionLine.bezierTo(cp21, cp22, p2, 100);
    motionLine.bezierTo(cp31, cp32, p3, 100);
    motionLine = motionLine.getResampledByCount(200);
    
    motionPct = 0.0;
    Tweenzor::add(&motionPct, motionPct, 1.0f, 0.0f, ofRandom(8, 12), EASE_IN_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&motionPct), this, &FishLike::onEndMove);
    
    bMoving = true;
    setPosition(from);
}

void FishLike::customDraw()
{
    ofVec2f rdmPos(ofRandom(-5, 5), ofRandom(-5, 5));
    ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
    float adjust = -ang + ((leftToRight) ? 110 : 70);
    
    ofPushMatrix();
    ofTranslate(rdmPos);
    ofScale(rdmScale);
    ofRotateZ(adjust);
    if (leftToRight)
        ofRotateX(180);
    texs.at(texIdx).draw(0, 0);
    ofPopMatrix();
}
