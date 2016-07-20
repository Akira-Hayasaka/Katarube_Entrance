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
    logoDur = package.getValue("logoDur", 0);
    infoDur = package.getValue("infoDur", 0);
    flushInkDur = package.getValue("flushInkDur", 0);
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
    if (appState == FLUSHINK)
    {
        if (Global::ELAPSED_TIME - flushInkBeginTime < 7)
        {
            for (int i = 0; i < 10; i++)
                ofNotifyEvent(Global::inkEvent);
        }
    }
    
    checkWorkFlow();
}

void WorkFlow::goCutout()
{
    appState = CUTOUT;
    ofNotifyEvent(Global::clearInkEvent);
    cutoutBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goLogo()
{
    appState = LOGO;
    ofNotifyEvent(Global::beginLogoEvent);
    logoBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goInfo()
{
    appState = INFO;
    ofNotifyEvent(Global::beginInfoEvent);
    infoBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goFlushInk()
{
    appState = FLUSHINK;
    flushInkBeginTime = Global::ELAPSED_TIME;
}

void WorkFlow::goInteractive()
{
    appState = INTERACTION;
}

string WorkFlow::getCurStateStr()
{
    if (appState == CUTOUT)
        return "CUTOUT";
    if (appState == LOGO)
        return "LOGO";
    if (appState == INFO)
        return "INFO";
    if (appState == FLUSHINK)
        return "FLUSHSCREEN";
    if (appState == INTERACTION)
        return "INTERACTION";
}

void WorkFlow::checkWorkFlow()
{
    
    
    
    proceedIfPossible();
}

void WorkFlow::proceedIfPossible()
{
    // loop if no interaction
    if (appState != INTERACTION)
    {
        if (appState == CUTOUT)
        {
            if (Global::ELAPSED_TIME - cutoutBeginTime > cutoutDur)
            {
                goLogo();
            }
        }
        if (appState == LOGO)
        {
            if (Global::ELAPSED_TIME - logoBeginTime > logoDur)
            {
                goInfo();
            }
        }
        if (appState == INFO)
        {
            if (Global::ELAPSED_TIME - infoBeginTime > infoDur)
            {
                goFlushInk();
            }
        }
        if (appState == FLUSHINK)
        {
            if (Global::ELAPSED_TIME - flushInkBeginTime > flushInkDur)
            {
                goCutout();
            }
        }
    }
}