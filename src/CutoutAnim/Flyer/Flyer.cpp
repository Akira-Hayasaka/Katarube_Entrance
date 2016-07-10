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
    
    fishLike.setPosition(700, 500, 0);
    wavy.setPosition(2100, 500, 0);
    strtThing.setPosition(2700, 500, 0);

    ofAddListener(Global::tickEvent, this, &Flyer::onTickEvent);
}

void Flyer::update()
{
    fishLike.update();
    wavy.update();
    strtThing.update();
}

void Flyer::onTickEvent()
{
    scrn.begin();
    ofClear(255);
    fishLike.draw();
    wavy.draw();
    strtThing.draw();
    scrn.end();
}

void Flyer::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}
