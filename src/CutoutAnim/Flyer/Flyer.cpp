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
    
    ofAddListener(Global::tickEvent, this, &Flyer::onTickEvent);
}

void Flyer::update()
{
    
}

void Flyer::onTickEvent()
{
    
}

void Flyer::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}
