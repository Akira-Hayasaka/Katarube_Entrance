//
//  Kyo.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/12/16.
//
//

#include "Kyo.hpp"

void Kyo::setup()
{
    scrn.allocate(APP_W, APP_H);
    clearScrn();
    
    ofAddListener(Global::tickEvent, this, &Kyo::onTickEvent);
}

void Kyo::update()
{
    
}

void Kyo::onTickEvent()
{
    
}

void Kyo::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}