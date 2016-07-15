//
//  KnifeTexture.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/13/16.
//
//

#ifndef KnifeTexture_hpp
#define KnifeTexture_hpp

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "Globals.hpp"

class KnifeTexture : public ofTexture, ofNode
{
public:
    
    enum STATE
    {
        NONE,
        CIRC,
        LINE
    };
    
    void setup(int idx, int numkNives);
    void update();
    void draw() { ofNode::draw(); }
    virtual void customDraw();
    void goCircle(ofPoint from, ofPoint interp, ofPoint to);
    void goLine(ofPolyline motionLine);
    STATE getState() { return state; }
    
private:
    
    STATE state;
    
    int idx;
    int numkNives;
    ofPolyline motionLine;
    float ang;
    ofPoint curPos;
    
    // circ
    ofPoint from;
    ofPoint interp;
    ofPoint to;
    float circBeginTime;
    float circShowDur;
    float circShowDelay;
    void onEndInterp(float* arg);
    void onEndCircle(float* arg);
};

#endif /* KnifeTexture_hpp */
