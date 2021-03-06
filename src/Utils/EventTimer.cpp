//
//  EventTimer.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#include "EventTimer.hpp"

void EventTimer::setInterval(float rdmFrom, float rdmTo)
{
    this->rdmFrom = rdmFrom;
    this->rdmTo = rdmTo;
    interval = ofRandom(rdmFrom, rdmTo);;
    lastEmittedTime = Globals::ELAPSED_TIME;
}

void EventTimer::update()
{
    if (Globals::ELAPSED_TIME - lastEmittedTime >= interval)
    {
        ofNotifyEvent(event);
        interval = ofRandom(rdmFrom, rdmTo);        
        lastEmittedTime = Globals::ELAPSED_TIME;
    }
}