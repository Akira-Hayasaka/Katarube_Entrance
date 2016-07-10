//
//  FlyerBase.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#include "FlyerBase.hpp"

void FlyerBase::setup(string seqDir)
{
    ofDirectory dir(seqDir);
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
    texIdx = 0;
    
    lastTickFrame = Global::curTickFrame;
    
    ofAddListener(Global::tickEvent, this, &FlyerBase::onTickEvent);
}

void FlyerBase::update()
{
    
}

void FlyerBase::customDraw()
{
    texs.at(texIdx).draw(0, 0);
}

void FlyerBase::onTickEvent()
{
    if (Global::curTickFrame - lastTickFrame > ofRandom(1, 3))
    {
        lastTickFrame = Global::curTickFrame;
        texIdx++;
        if (texIdx >= texs.size())
            texIdx = 0;
    }
}