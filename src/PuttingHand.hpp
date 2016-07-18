//
//  PuttingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef PuttingHand_hpp
#define PuttingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "BodyState.hpp"

class PuttingHand
{
public:
    
    void setup(BodyBase* bodyBase);
    void draw();
    void onPutEvent();    
    bool isDone() { return (bodyState.state == BodyState::DONE) ? true : false; }
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEndEmerge(float* arg);
    void onEndRetire(float* arg);    
    
    float startDoingTime;
    float doingDur;
    
    BodyState bodyState;
    BodyBase* bodyBase;
};

#endif /* PuttingHand_hpp */
