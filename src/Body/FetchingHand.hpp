//
//  FetchingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef FetchingHand_hpp
#define FetchingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "BodyState.hpp"

class FetchingHand
{
public:
    
    void setup(BodyBase* bodyBase);
    void draw();
    void onFetchEvent();    
    bool isDone() { return (bodyState.state == BodyState::DONE) ? true : false; }    
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEndEmerge(float* arg);
    
    float startDoingTime;
    float doingDur;
    
    BodyState bodyState;
    BodyBase* bodyBase;
};

#endif /* FetchingHand_hpp */
