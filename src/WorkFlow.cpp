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
    ofxXmlSettings package;
    package.load("package.xml");
    package.pushTag("workflow");
    cutoutDur = package.getValue("cutoutDur", 0);
    logoInfoDur = package.getValue("logoInfoDur", 0);
    flushScreenDur = package.getValue("flushScreenDur", 0);
    package.popTag();

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
    
    proceed();
}

void WorkFlow::goCutout()
{
    appState = CUTOUT;
    cutoutBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goLogoInfo()
{
    appState = LOGOINFO;
    ofNotifyEvent(Global::beginLogoInfoEvent);
    logoInfoBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goFlushScreen()
{
    appState = FLUSHSCREEN;
    flushSceenBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goInteractive()
{
    
}

void WorkFlow::proceed()
{
    // loop if no interaction
    if (appState != INTERACTION)
    {
        if (appState == CUTOUT)
        {
            if (Global::ELAPSED_TIME - cutoutBeginTime > cutoutDur)
            {
                goLogoInfo();
            }
        }
        if (appState == LOGOINFO)
        {
            if (Global::ELAPSED_TIME - logoInfoBeginTime > logoInfoDur)
            {
                goFlushScreen();
            }
        }
        if (appState == FLUSHSCREEN)
        {
            if (Global::ELAPSED_TIME - flushSceenBeginTime > flushScreenDur)
            {
                goCutout();
            }
        }
    }
}

string WorkFlow::getCurStateStr()
{
    if (appState == CUTOUT)
        return "CUTOUT";
    if (appState == LOGOINFO)
        return "LOGOINFO";
    if (appState == FLUSHSCREEN)
        return "FLUSHSCREEN";
    if (appState == INTERACTION)
        return "INTERACTIO";
}