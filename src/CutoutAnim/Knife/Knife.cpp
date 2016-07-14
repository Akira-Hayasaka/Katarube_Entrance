//
//  Knife.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#include "Knife.hpp"

void Knife::setup()
{
    scrn.allocate(APP_W, APP_H);
    clearScrn();
    
    
    
    ofAddListener(Global::tickEvent, this, &Knife::onTickEvent);
}

void Knife::update()
{

}

void Knife::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Knife::onTickEvent()
{
//    scrn.begin();
//    ofClear(255);
//    texs.at(0).draw(500, 500);
//    scrn.end();
}