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
    ofAddListener(Global::portraitHorizEvent, this, &Portrait::onPortraitHorizEvent);
    
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
        
        scrn.begin();
        ofClear(255);
        beginShake(onePlacePos);
        texs.at(texIdx).draw(0, 0);
        endShake();
        scrn.end();
        
        if (texIdx >= texs.size() - 1)
        {
            texIdx = 0;
            clearScrn();
            pattern = NONE;
        }
    }
    else if (pattern == HORIZ)
    {
        if (Global::curTickFrame - lastOneFrameTick > horixStartInterval)
        {
            horizStartIdx++;
            if (horizStartIdx < texs.size())
            {
                Tweenzor::add(&curHorizPos.at(horizStartIdx).x, curHorizPos.at(horizStartIdx).x, horizTos.at(horizStartIdx).x, 0.0f, 10.0f, EASE_IN_OUT_SINE);
                Tweenzor::addCompleteListener(Tweenzor::getTween(&curHorizPos.at(horizStartIdx).x), this, &Portrait::onEndOneHorizMovement);
            }
            lastOneFrameTick = Global::curTickFrame;
        }
        
        scrn.begin();
        ofClear(255);
        ofPushMatrix();
        ofTranslate(horizRotCen);
        ofRotate(horizRot);
        ofTranslate(-horizRotCen);
        for (int i = 0; i < texs.size(); i++)
        {
            beginShake(curHorizPos.at(i), 0.7);
            texs.at(i).draw(0, 0);
            endShake();
        }
        ofPopMatrix();
        scrn.end();
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

void Portrait::onPortraitHorizEvent()
{
    if (pattern == NONE)
    {
        pattern = HORIZ;
        beginTickFrame = Global::curTickFrame;
        lastOneFrameTick = Global::curTickFrame;
        ofSort(texs, compareHeight);
        horizFroms.clear(); horizFroms.resize(texs.size());
        horizTos.clear(); horizTos.resize(texs.size());
        curHorizPos.clear(); curHorizPos.resize(texs.size());
        for (int i = 0; i < texs.size(); i++)
        {
            horizFroms.at(i).set(100, APP_H/2 + 300 - texs.at(i).getHeight()/2, 0);
            horizTos.at(i).set(APP_W - 100, APP_H/2 + 300 - texs.at(i).getHeight()/2, 0);
            curHorizPos.at(i) = horizFroms.at(i);
        }
        horizStartIdx = 0;
        Tweenzor::add(&curHorizPos.at(horizStartIdx).x, curHorizPos.at(horizStartIdx).x, horizTos.at(horizStartIdx).x, 0.0f, 10.0f, EASE_IN_OUT_SINE);
        Tweenzor::addCompleteListener(Tweenzor::getTween(&curHorizPos.at(horizStartIdx).x), this, &Portrait::onEndOneHorizMovement);
        
        horixStartInterval = 5;
        horizFinishCnt = 0;
        
        horizRot = ofRandom(-20, 20);
        horizRotCen.set(APP_W/2 + ofRandom(-100, 100), APP_H/2 + ofRandom(-100, 100));
    }
}

void Portrait::beginShake(ofPoint pos, float scaleF)
{
    ofVec2f rdmPos(pos.x + ofRandom(-5, 5), pos.y + ofRandom(-5, 5));
    ofVec2f rdmScale(scaleF * ofRandom(0.77, 0.8), scaleF * ofRandom(0.77, 0.8));
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofPushMatrix();
    ofTranslate(rdmPos);
    ofScale(rdmScale);
}

void Portrait::endShake()
{
    ofPopMatrix();
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void Portrait::onEndOneHorizMovement(float* arg)
{
    horizFinishCnt++;
    if (horizFinishCnt >= texs.size())
        pattern = NONE;
}