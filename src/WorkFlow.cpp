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

    EventTimer portraitOnePlaceEventTimer(Globals::portraitOnePlaceEvent);
    portraitOnePlaceEventTimer.setInterval(4.0, 5.0);
    cutoutEvents.push_back(portraitOnePlaceEventTimer);
    EventTimer portraitHorizEventTimer(Globals::portraitHorizEvent);
    portraitHorizEventTimer.setInterval(15.0, 20.0);
    cutoutEvents.push_back(portraitHorizEventTimer);
    EventTimer portraitVertEventTimer(Globals::portraitVertEvent);
    portraitVertEventTimer.setInterval(10.0, 15.0);
    cutoutEvents.push_back(portraitVertEventTimer);
    EventTimer flyerFishLikeEventTimer(Globals::flyerFishLikeEvent);
    flyerFishLikeEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerFishLikeEventTimer);
    EventTimer flyerWavyEventTimer(Globals::flyerWavyEvent);
    flyerWavyEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerWavyEventTimer);
    EventTimer flyerStraightThingEventTimer(Globals::flyerStraightThingEvent);
    flyerStraightThingEventTimer.setInterval(1.0, 7.0);
    cutoutEvents.push_back(flyerStraightThingEventTimer);
    EventTimer kyoEventTimer(Globals::kyoEvent);
    kyoEventTimer.setInterval(0.5, 1.0);
    cutoutEvents.push_back(kyoEventTimer);
    EventTimer knifeCircleEventTimer(Globals::knifeCircleEvent);
    knifeCircleEventTimer.setInterval(1.0, 2.0);
    cutoutEvents.push_back(knifeCircleEventTimer);
}

void WorkFlow::update()
{
    checkWorkFlow();
}

void WorkFlow::goCutout()
{
    appState = CUTOUT;
    ofNotifyEvent(Globals::fadeInCutoutEvent);
    cutoutBeginTime = Globals::ELAPSED_TIME;
}

void WorkFlow::goLogo()
{
    appState = LOGO;
    ofNotifyEvent(Globals::beginLogoEvent);
    logoBeginTime = Globals::ELAPSED_TIME;
    bFadeOutLogo = false;
}

void WorkFlow::goInfo()
{
    appState = INFO;
    ofNotifyEvent(Globals::beginInfoEvent);
    infoBeginTime = Globals::ELAPSED_TIME;
    bFadeOutInfo = false;
}

void WorkFlow::goFlushInk()
{
    appState = FLUSHINK;
    flushInkBeginTime = Globals::ELAPSED_TIME;
    bFadeOutInk = false;
}

void WorkFlow::goInteractive()
{
    appState = INTERACTION;
    ofNotifyEvent(Globals::fadeOutCutoutEvent);
    ofNotifyEvent(Globals::fadeOutLogoEvent);
    ofNotifyEvent(Globals::fadeOutInfoEvent);
    ofNotifyEvent(Globals::fadeOutInkEvent);
    ofNotifyEvent(Globals::handRetireEvent);
    ofNotifyEvent(Globals::swipeEvent);
    interactionBeginTime = Globals::ELAPSED_TIME;
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
    if (appState == CUTOUT)
    {
        for (auto& et : cutoutEvents)
            et.update();
        
        if (Globals::ELAPSED_TIME - cutoutBeginTime > 3.0 && !bFadeOutLogo)
        {
            ofNotifyEvent(Globals::fadeOutLogoEvent);
            bFadeOutLogo = true;
        }
        
        if (Globals::ELAPSED_TIME - cutoutBeginTime > 4.0 && !bFadeOutInfo)
        {
            ofNotifyEvent(Globals::fadeOutInfoEvent);
            bFadeOutInfo = true;
        }
    }
    if (appState == FLUSHINK)
    {
#ifdef TARGET_WIN32
        if (Globals::ELAPSED_TIME - flushInkBeginTime < 6)
        {
            for (int i = 0; i < 1; i++)
                ofNotifyEvent(Globals::inkEvent);
        }
#else
        if (Globals::ELAPSED_TIME - flushInkBeginTime < 7)
        {
            for (int i = 0; i < 10; i++)
                ofNotifyEvent(Globals::inkEvent);
        }
#endif
        
        if (Globals::ELAPSED_TIME - flushInkBeginTime > flushInkDur - 1.0 && !bFadeOutInk)
        {
            ofNotifyEvent(Globals::fadeOutInkEvent);
            bFadeOutInk = true;
        }
    }
    if (appState == INTERACTION)
    {
        
    }
    
    proceedIfPossible();
}

void WorkFlow::proceedIfPossible()
{
    // loop if no interaction
    if (appState != INTERACTION)
    {
        if (appState == CUTOUT)
        {
            if (Globals::ELAPSED_TIME - cutoutBeginTime > cutoutDur)
            {
                goLogo();
            }
        }
        if (appState == LOGO)
        {
            if (Globals::ELAPSED_TIME - logoBeginTime > logoDur)
            {
                goInfo();
            }
        }
        if (appState == INFO)
        {
            if (Globals::ELAPSED_TIME - infoBeginTime > infoDur)
            {
                goFlushInk();
            }
        }
        if (appState == FLUSHINK)
        {
            if (Globals::ELAPSED_TIME - flushInkBeginTime > flushInkDur)
            {
                goCutout();
            }
        }
    }
}