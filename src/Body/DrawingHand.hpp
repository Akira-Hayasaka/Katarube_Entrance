//
//  DrawingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef DrawingHand_hpp
#define DrawingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "BodyState.hpp"

class DrawingHand
{
public:
    
    void setup(BodyBase* bodyBase);
    void draw();
    void onDrawEvent(ofPoint dest);
    bool isDone() { return (bodyState.state == BodyState::DONE) ? true : false; }    
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEndEmerge(float* arg);
    void onEndRetire(float* arg);
    
    float startDoingTime;
    float doingDur;
    bool bFromUpper;
    float ang;
    
    BodyState bodyState;
    BodyBase* bodyBase;
};

#endif /* DrawingHand_hpp */
