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
    
    lastTickFrame = Global::curTickFrame;
    texIdx = 0;
    bMoving = false;
}

void FlyerBase::update()
{
    if (bMoving)
    {
        int vIdx = ofMap(motionPct, 0.0, 1.0, 0, motionLine.getVertices().size()-1);
        ofVec2f cur = motionLine.getVertices().at(vIdx);
        setPosition(cur);
        
        ofVec2f next;
        if (vIdx >= motionLine.getVertices().size()-1)
            next = motionLine.getVertices().at(0);
        else
            next = motionLine.getVertices().at(vIdx+1);
        
        ofVec2f dv = cur - next;
        ang = atan2(dv.x, dv.y) * 180 / PI;
    }
}

void FlyerBase::onTick()
{
    if (Global::curTickFrame - lastTickFrame > ofRandom(1, 3))
    {
        lastTickFrame = Global::curTickFrame;
        texIdx++;
        if (texIdx >= texs.size())
            texIdx = 0;
    }
}
