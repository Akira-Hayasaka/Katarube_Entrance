//
//  Flyer.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#include "Flyer.hpp"

void Flyer::setup()
{
    scrn.allocate(APP_W, APP_H);
    clearScrn();
    
    fishLike.setup("imgs/cutoutAnim/flyer/1");
    wavy.setup("imgs/cutoutAnim/flyer/2");
    strtThing.setup("imgs/cutoutAnim/flyer/3");

    ofAddListener(Globals::tickEvent, this, &Flyer::onTickEvent);
    ofAddListener(Globals::flyerFishLikeEvent, this, &Flyer::onFlyerFishLikeEvent);
    ofAddListener(Globals::flyerWavyEvent, this, &Flyer::onFlyerWavyEvent);
    ofAddListener(Globals::flyerStraightThingEvent, this, &Flyer::onFlyerStraightThingEvent);
}

void Flyer::update()
{
    for (auto& fl : fishLikes)
        fl.update();
    if (!fishLikes.empty())
    {
        if (!fishLikes.front().isMoving())
            fishLikes.pop_front();
    }
    
    for (auto& w : wavys)
        w.update();
    if (!wavys.empty())
    {
        if (!wavys.front().isMoving())
            wavys.pop_front();
    }
    
    for (auto& s : strtThings)
        s.update();
    if (!strtThings.empty())
    {
        if (!strtThings.front().isMoving())
            strtThings.pop_front();
    }
}

void Flyer::onTickEvent()
{
    scrn.begin();
    ofClear(255);
    for (auto& fl : fishLikes)
    {
        fl.onTick();
        fl.draw();
    }
    for (auto& w : wavys)
    {
        w.onTick();
        w.draw();
    }
    for (auto& s : strtThings)
    {
        s.onTick();
        s.draw();
    }
    scrn.end();
}

void Flyer::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Flyer::onFlyerFishLikeEvent()
{
    FishLike fl = fishLike;
    fishLikes.push_back(fl);
    fishLikes.back().go();
}

void Flyer::onFlyerWavyEvent()
{
    Wavy w = wavy;
    wavys.push_back(w);
    wavys.back().go();
}

void Flyer::onFlyerStraightThingEvent()
{
    StraightThing s = strtThing;
    strtThings.push_back(s);
    strtThings.back().go();
}