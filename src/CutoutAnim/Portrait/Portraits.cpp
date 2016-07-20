//
//  Portraits.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#include "Portraits.hpp"

void Portraits::setup()
{
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
    
    ofPolyline b2dEdgeTweak = Globals::b2dEdge;
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
            bottomLineAndAngSimplified.push_back(ba);
        }
    }
    
    texIdx = 0;
    
    pattern = NONE;
}

void Portraits::update()
{
    checkDone();
}

void Portraits::onTick()
{
    if (pattern == ONEPLACE)
    {
        if (Globals::curTickFrame - lastOneFrameTick > onPlaceFrameDur)
        {
            texIdx++;
            onPlaceFrameDur = ofRandom(10);
            lastOneFrameTick = Globals::curTickFrame;
        }
        
        texs.at(texIdx).draw();
        
        if (texIdx >= texs.size() - 1)
        {
            texIdx = 0;
            pattern = DONE;
        }
    }
    else if (pattern == HORIZ)
    {
        ofPushMatrix();
        ofTranslate(horizRotCen);
        ofRotate(horizRot);
        ofTranslate(-horizRotCen);
        for (int i = 0; i < texs.size(); i++)
            texs.at(i).draw(0.7);
        ofPopMatrix();
    }
    else if (pattern == VERT)
    {
        for (int i = 0; i < texs.size(); i++)
            texs.at(i).draw(0.6);
    }
}

void Portraits::onPortraitOnePlace()
{
    if (pattern == NONE)
    {
        pattern = ONEPLACE;
        beginTickFrame = Globals::curTickFrame;
        lastOneFrameTick = Globals::curTickFrame;
        onPlaceFrameDur = ofRandom(3);
        ofRandomize(texs);
        ofPoint rdmPos(ofRandom(370, 3440), ofRandom(370, 790));
        int nearestIdx = 0;
        vector<ofPoint> btmLine;
        for (auto bl : Globals::bottomLineAndAngs)
            btmLine.push_back(bl.p);
        getNearestPt(btmLine, rdmPos, nearestIdx);
        onePlaceAng = Globals::bottomLineAndAngs.at(nearestIdx).ang;
        for (auto& t : texs)
            t.doOnePlace(rdmPos, onePlaceAng);
    }
}

void Portraits::onPortraitHoriz()
{
    if (pattern == NONE)
    {
        pattern = HORIZ;
        workingTexs.clear();
        beginTickFrame = Globals::curTickFrame;
        lastOneFrameTick = Globals::curTickFrame;
        
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

void Portraits::onPortraitVert()
{
    if (pattern == NONE)
    {
        pattern = VERT;
        workingTexs.clear();
        beginTickFrame = Globals::curTickFrame;
        lastOneFrameTick = Globals::curTickFrame;
        
        ofRandomize(texs);
        int numVertAction = 15;
        int step = bottomLineAndAngSimplified.size() / numVertAction;
        int skipInitPts = 5;
        for (int i = 0; i < numVertAction; i++)
        {
            ofPoint from(bottomLineAndAngSimplified.at(skipInitPts+i*step).p.x,
                         bottomLineAndAngSimplified.at(skipInitPts+i*step).p.y + texs.at(i).getHeight()/2 + 10);
            ofPoint to(from.x, from.y - texs.at(i).getHeight() * 0.75);
            ofPoint cur = from;
            texs.at(i).doVert(i, bottomLineAndAngSimplified.at(skipInitPts+i*step).ang, from, to, cur);
            workingTexs.push_back(&texs.at(i));
        }
    }
}

void Portraits::checkDone()
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
            pattern = DONE;
    }
}
