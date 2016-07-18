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

class SwipingHand : public BodyBase
{
public:
    
    void setup(string seqDirPath);
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onSwipeEvent();
    void onEndSwipe(float* arg);
    
    float startDoingTime;
    float doingDur;
};

#endif /* SwipingHand_hpp */
