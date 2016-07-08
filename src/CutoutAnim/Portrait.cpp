//
//  Portrait.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#include "Portrait.hpp"

void Portrait::setup()
{
    scrn.allocate(APP_W, APP_H);
    
    ofDirectory dir;
    dir.open("imgs/cutoutAnim/portrait");
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
    
    ofAddListener(Global::tickEvent, this, &Portrait::onTickEvent);
    ofAddListener(Global::portraitOnePlaceEvent, this, &Portrait::onPortraitOnePlaceEvent);
    
    texIdx = 0;
    
    pattern = NONE;
    clearScrn();
}

void Portrait::update()
{

}

void Portrait::onTickEvent()
{
    if (pattern == ONEPLACE)
    {
        if (Global::curTickFrame - lastOneFrameTick > onPlaceFrameDur)
        {
            texIdx++;
            onPlaceFrameDur = ofRandom(10);
            lastOneFrameTick = Global::curTickFrame;
        }
        
        ofVec2f rdmPos(onePlacePos.x + ofRandom(-5, 5), onePlacePos.y + ofRandom(-5, 5));
        ofVec2f rdmScale(ofRandom(0.77, 0.8), ofRandom(0.77, 0.8));
        scrn.begin();
        ofClear(255);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofPushMatrix();
        ofTranslate(rdmPos);
        ofScale(rdmScale);
        texs.at(texIdx).draw(0, 0);
        ofPopMatrix();
        ofSetRectMode(OF_RECTMODE_CORNER);
        scrn.end();
        
        if (texIdx >= texs.size() - 1)
        {
            texIdx = 0;
            clearScrn();
            pattern = NONE;
        }
    }
}

void Portrait::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Portrait::onPortraitOnePlaceEvent()
{
    if (pattern == NONE)
    {
        pattern = ONEPLACE;
        beginTickFrame = Global::curTickFrame;
        lastOneFrameTick = Global::curTickFrame;
        onPlaceFrameDur = ofRandom(3);
        ofRandomize(texs);
        onePlacePos.set(ofRandom(370, 3440), ofRandom(370, 790));
    }
}