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
    
    ofDirectory dir;
    dir.open("imgs/cutoutAnim/knife/0");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofFile f = dir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
        {
            ofTexture t;
            texs.push_back(t);
            ofLoadImage(texs.back(), f.getAbsolutePath());
        }
    }
    dir.close();
    
    ofAddListener(Global::tickEvent, this, &Knife::onTickEvent);
    bNeedTickUpdate = false;
}

void Knife::update()
{
    
    if (bNeedTickUpdate)
    {
        scrn.begin();
        ofClear(255);
        texs.at(0).draw(500, 500);
        scrn.end();
        bNeedTickUpdate = false;
    }
}

void Knife::onTickEvent()
{
    bNeedTickUpdate = true;
}