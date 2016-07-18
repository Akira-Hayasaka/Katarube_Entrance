//
//  SwipingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef SwipingHand_hpp
#define SwipingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "BodyState.hpp"

class SwipingHand
{
public:
    
    void setup(BodyBase* bodyBase);
    void draw();
    void onSwipeEvent();    
    bool isDone() { return (bodyState.state == BodyState::DONE) ? true : false; }
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEndSwipe(float* arg);
    
    float startDoingTime;
    float doingDur;
    
    BodyState bodyState;
    BodyBase* bodyBase;
};

#endif /* SwipingHand_hpp */
