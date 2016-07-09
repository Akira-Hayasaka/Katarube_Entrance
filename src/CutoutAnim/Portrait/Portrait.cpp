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
            PortraitTexture t;
            texs.push_back(t);
            texs.back().setup(f.getAbsolutePath());
        }
    }
    dir.close();
    
    ofPolyline b2dEdgeTweak = Global::b2dEdge;
//    b2dEdgeTweak = b2dEdgeTweak.getResampledByCount(texs.size() * 2);
    for (int i = 0; i < b2dEdgeTweak.getVertices().size(); i++)
    {
        ofVec2f perp;
        if (i == b2dEdgeTweak.getVertices().size()-1)
            perp = ofVec2f(b2dEdgeTweak.getVertices().at(i) - b2dEdgeTweak.getVertices().at(0)).getPerpendicular();
        else
            perp = ofVec2f(b2dEdgeTweak.getVertices().at(i) - b2dEdgeTweak.getVertices().at(i+1)).getPerpendicular();
        
        float ang = ofVec2f(0, -1).angle(perp);
        if (fabs(ang) < 90)
        {
            BottomLineAndAng ba;
            ba.p = b2dEdgeTweak.getVertices().at(i);
            ba.ang = ang;
            bottomLineAndAngs.push_back(ba);
        }
    }
    
    ofAddListener(Global::tickEvent, this, &Portrait::onTickEvent);
    ofAddListener(Global::portraitOnePlaceEvent, this, &Portrait::onPortraitOnePlaceEvent);
    ofAddListener(Global::portraitHorizEvent, this, &Portrait::onPortraitHorizEvent);
    ofAddListener(Global::portraitVertEvent, this, &Portrait::onPortraitVertEvent);    
    
    texIdx = 0;
    
    pattern = NONE;
    clearScrn();
}

void Portrait::update()
{
    for (auto& t : texs)
        t.update();
    
    checkDone();
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
        texs.at(texIdx).draw();
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
        scrn.begin();
        ofClear(255);
        ofPushMatrix();
        ofTranslate(horizRotCen);
        ofRotate(horizRot);
        ofTranslate(-horizRotCen);
        for (int i = 0; i < texs.size(); i++)
            texs.at(i).draw(0.7);
        ofPopMatrix();
        scrn.end();
    }
    else if (pattern == VERT)
    {
        scrn.begin();
        ofClear(255);
        for (int i = 0; i < texs.size(); i++)
            texs.at(i).draw(0.6);
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
        for (auto& t : texs)
            t.doOnePlace(ofPoint(ofRandom(370, 3440), ofRandom(370, 790)));
    }
}

void Portrait::onPortraitHorizEvent()
{
    if (pattern == NONE)
    {
        pattern = HORIZ;
        workingTexs.clear();
        beginTickFrame = Global::curTickFrame;
        lastOneFrameTick = Global::curTickFrame;
        
        ofSort(texs, compareHeight);
        for (int i = 0; i < texs.size(); i++)
        {
            texs.at(i).doHoriz(i,
                               ofPoint(100, APP_H/2 + 300 - texs.at(i).getHeight()/2, 0),
                               ofPoint(APP_W - 100, APP_H/2 + 300 - texs.at(i).getHeight()/2, 0),
                               ofPoint(100, APP_H/2 + 300 - texs.at(i).getHeight()/2, 0));
            workingTexs.push_back(&texs.at(i));
        }

        horizRot = ofRandom(-20, 20);
        horizRotCen.set(APP_W/2 + ofRandom(-100, 100), APP_H/2 + ofRandom(-100, 100));
    }
}

void Portrait::onPortraitVertEvent()
{
    if (pattern == NONE)
    {
        pattern = VERT;
        workingTexs.clear();
        beginTickFrame = Global::curTickFrame;
        lastOneFrameTick = Global::curTickFrame;
        ofRandomize(texs);
        int numVertAction = 15;
        int step = bottomLineAndAngs.size() / numVertAction;
        int skipInitPts = 5;
        for (int i = 0; i < numVertAction; i++)
        {
            ofPoint from(bottomLineAndAngs.at(skipInitPts+i*step).p.x, bottomLineAndAngs.at(skipInitPts+i*step).p.y + texs.at(i).getHeight()/2 + 10);
            ofPoint to(from.x, from.y - texs.at(i).getHeight() * 0.75);
            ofPoint cur = from;
            texs.at(i).doVert(i, bottomLineAndAngs.at(skipInitPts+i*step).ang, from, to, cur);
            workingTexs.push_back(&texs.at(i));
        }
    }
}

void Portrait::checkDone()
{
    if (pattern == HORIZ || pattern == VERT)
    {
        int finCnt = 0;
        for (auto t : workingTexs)
        {
            if (t->isDone())
                finCnt++;
        }
        if (finCnt >= workingTexs.size())
            pattern = NONE;
    }
}
