//
//  Portrait.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#include "Portrait.hpp"

void Portrait::setup()
{
    scrn.allocate(APP_W, APP_H);
    clearScrn();
    
    portrait.setup();
    
    ofAddListener(Global::tickEvent, this, &Portrait::onTickEvent);
    ofAddListener(Global::portraitOnePlaceEvent, this, &Portrait::onPortraitOnePlaceEvent);
    ofAddListener(Global::portraitHorizEvent, this, &Portrait::onPortraitHorizEvent);
    ofAddListener(Global::portraitVertEvent, this, &Portrait::onPortraitVertEvent);
}

void Portrait::update()
{
    for (auto& w : worksets)
        w.update();
    if (!worksets.empty())
    {
        if (worksets.front().isDone())
            worksets.pop_front();
    }
}

void Portrait::onTickEvent()
{
    scrn.begin();
    ofClear(255);
    for (auto& w : worksets)
        w.onTick();
    scrn.end();
}

void Portrait::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Portrait::onPortraitOnePlaceEvent()
{
    worksets.push_back(portrait);
    worksets.back().onPortraitOnePlace();
}

void Portrait::onPortraitHorizEvent()
{
    worksets.push_back(portrait);
    worksets.back().onPortraitHoriz();
}

void Portrait::onPortraitVertEvent()
{
    worksets.push_back(portrait);
    worksets.back().onPortraitVert();
}

