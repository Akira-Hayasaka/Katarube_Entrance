//
//  FlyerBase.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef FlyerBase_hpp
#define FlyerBase_hpp

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"

class FlyerBase : public ofNode
{
public:
    
    void setup(string seqDir);
    void update();
    void onTick();    
    ofPolyline& getMotionLine() { return motionLine; }
    bool isMoving() { return bMoving; }
    
    virtual void go() = 0;
    
protected:
    
    
    int lastTickFrame;
    
    int texIdx;
    vector<ofTexture> texs;
    
    bool bMoving;
    ofPolyline motionLine;
    float motionPct;
    float ang;
};

#endif /* FlyerBase_hpp */
