//
//  EventTimer.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#ifndef EventTimer_hpp
#define EventTimer_hpp

#include "ofMain.h"
#include "Globals.hpp"

class EventTimer
{
public:
    
    EventTimer(ofEvent<void>& event) : event(event) {}
    void setInterval(float rdmFrom, float rdmTo);
    void update();
    
    ofEvent<void>& event;
    
private:
    
    float interval;
    float rdmFrom, rdmTo;
    float lastEmittedTime;
};

#endif /* EventTimer_hpp */
