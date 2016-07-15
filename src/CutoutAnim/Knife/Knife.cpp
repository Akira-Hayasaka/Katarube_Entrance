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
    
    ofDirectory dir("imgs/cutoutAnim/knife");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        if (dir.getFile(i).isDirectory())
        {
            Knives k;
            knives.push_back(k);
            knives.back().setup(dir.getFile(i).getAbsolutePath());
        }
    }
    dir.close();
    
    ofAddListener(Global::tickEvent, this, &Knife::onTickEvent);
    ofAddListener(Global::knifeCircleEvent, this, &Knife::onKnifeCircleEvent);
}

void Knife::update()
{
    for (auto& w : worksets)
        w.update();
    if (!worksets.empty())
    {
        if (!worksets.front().isRunning())
            worksets.pop_front();
    }
}

void Knife::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Knife::onTickEvent()
{
    scrn.begin();
    ofClear(255);
    for (auto w : worksets)
        w.draw();
    scrn.end();
}

void Knife::onKnifeCircleEvent()
{
    worksets.push_back(knives.at(ofRandom(knives.size()-1)));
    worksets.back().goCircle();
}