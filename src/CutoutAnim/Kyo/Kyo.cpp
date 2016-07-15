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
    
    ofDirectory dir("imgs/cutoutAnim/kyo");
    dir.listDir();
    for (int i = 0; i < dir.size(); i++)
    {
        ofFile f = dir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
        {
            KyoTexture t;
            texs.push_back(t);
            ofLoadImage(texs.back(), f.getAbsolutePath());
        }
    }
    dir.close();
    
    curIdx = 0;
    
    ofAddListener(Global::tickEvent, this, &Kyo::onTickEvent);
    ofAddListener(Global::kyoEvent, this, &Kyo::onKyoEvent);
}

void Kyo::update()
{
    if (!worksets.empty())
    {
        if (!worksets.front().isRunning())
            worksets.pop_front();
    }
}

void Kyo::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Kyo::onTickEvent()
{
    scrn.begin();
    ofClear(255);
    for (auto w : worksets)
        w.draw();
    scrn.end();
}

void Kyo::onKyoEvent()
{
    curIdx++;
    if (curIdx >= texs.size())
        curIdx = 0;
    worksets.push_back(texs.at(curIdx));
    worksets.back().go();
}
