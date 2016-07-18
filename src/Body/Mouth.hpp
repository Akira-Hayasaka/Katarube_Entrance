//
//  Mouth.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#ifndef Mouth_hpp
#define Mouth_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "BodyState.hpp"

class Mouth
{
public:
    
    void setup(BodyBase* bodyBase);
    void draw();
    void onEatEvent();    
    bool isDone() { return (bodyState.state == BodyState::DONE) ? true : false; }    
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEndEmerge(float* arg);
    
    BodyState bodyState;
    BodyBase* bodyBase;
};

#endif /* Mouth_hpp */
