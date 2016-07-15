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
    
    curIdx = 0;
    
    ofAddListener(Global::tickEvent, this, &Knife::onTickEvent);
    ofAddListener(Global::knifeCircleEvent, this, &Knife::onKnifeCircleEvent);
}

void Knife::update()
{
    for (auto& k : knives)
        k.update();
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
    for (auto k : knives)
        k.draw();
    scrn.end();
}

void Knife::onKnifeCircleEvent()
{
    curIdx++;
    if (curIdx >= knives.size())
        curIdx = 0;
    knives.at(curIdx).goCircle();
}