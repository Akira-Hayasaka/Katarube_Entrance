//
//  WorkFlow.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#include "WorkFlow.hpp"

void WorkFlow::setup()
{
    appState = CUTOUT;

    EventTimer portraitOnePlaceEventTimer(Global::portraitOnePlaceEvent);
    portraitOnePlaceEventTimer.setInterval(4.0, 5.0);
    cutoutEvents.push_back(portraitOnePlaceEventTimer);
    EventTimer portraitHorizEventTimer(Global::portraitHorizEvent);
    portraitHorizEventTimer.setInterval(15.0, 20.0);
    cutoutEvents.push_back(portraitHorizEventTimer);
    EventTimer portraitVertEventTimer(Global::portraitVertEvent);
    portraitVertEventTimer.setInterval(10.0, 15.0);
    cutoutEvents.push_back(portraitVertEventTimer);
    EventTimer flyerFishLikeEventTimer(Global::flyerFishLikeEvent);
    flyerFishLikeEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerFishLikeEventTimer);
    EventTimer flyerWavyEventTimer(Global::flyerWavyEvent);
    flyerWavyEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerWavyEventTimer);
    EventTimer flyerStraightThingEventTimer(Global::flyerStraightThingEvent);
    flyerStraightThingEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerStraightThingEventTimer);
    EventTimer kyoEventTimer(Global::kyoEvent);
    kyoEventTimer.setInterval(0.5, 1.0);
    cutoutEvents.push_back(kyoEventTimer);
    EventTimer knifeCircleEventTimer(Global::knifeCircleEvent);
    knifeCircleEventTimer.setInterval(1.0, 2.0);
    cutoutEvents.push_back(knifeCircleEventTimer);
}

void WorkFlow::update()
{
    if (appState == CUTOUT)
    {
        for (auto& et : cutoutEvents)
            et.update();
    }
}

void WorkFlow::goCutout()
{
    
}

void WorkFlow::goFlushScreen()
{
    
}

void WorkFlow::goInteractive()
{
    
}
