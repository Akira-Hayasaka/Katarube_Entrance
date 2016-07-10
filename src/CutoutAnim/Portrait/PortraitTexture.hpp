//
//  PortraitTexture.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/9/16.
//
//

#ifndef PortraitTexture_hpp
#define PortraitTexture_hpp

#include "ofMain.h"
#include "ofxTweenzor.h"

class PortraitTexture : public ofTexture
{
public:
    
    void setup(string path);
    void update();
    void draw(float scaleF = 1.0);
    
    ofPoint getCur() { return cur; }
    
    bool isDone() { return bDone; }
    void doOnePlace(ofPoint cur, float ang);
    void doHoriz(int idx,
                 ofPoint from, ofPoint to, ofPoint cur);
    void doVert(int idx, float ang,
                ofPoint from, ofPoint to, ofPoint cur);
    
private:
    
    void onEndHoris(float* arg);
    void onEndVertUp(float* arg);
    void onEndVertDown(float* arg);
    
    bool bDone;
    int idx;
    ofPoint from;
    ofPoint to;
    ofPoint cur;
    float ang;
};

#endif /* PortraitTexture_hpp */
