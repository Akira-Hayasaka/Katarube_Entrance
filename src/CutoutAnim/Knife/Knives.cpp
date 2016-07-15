//
//  Knives.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/13/16.
//
//

#include "Knives.hpp"

void Knives::setup(string dirPath)
{
    ofDirectory dir(dirPath);
    dir.listDir();
    int numKnives = 0;
    for (int i = 0; i < dir.size(); i++)
    {
        ofFile f = dir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
            numKnives++;
    }
    int texIdx = 0;
    for (int i = 0; i < dir.size(); i++)
    {
        ofFile f = dir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
        {
            KnifeTexture kt;
            texs.push_back(kt);
            ofLoadImage(texs.back(), f.getAbsolutePath());
            texs.back().setup(texIdx, numKnives);
            texIdx++;
        }
    }
    dir.close();
    
    bRunning = false;
}

void Knives::update()
{
    if (bRunning)
    {
        int finNum = 0;
        for (auto& t : texs)
        {
            t.update();
            if (t.getState() == KnifeTexture::NONE)
                finNum++;
        }
        
        if (finNum >= texs.size())
            bRunning = false;
        
        rot += 0.5;
    }
}

void Knives::draw()
{
    if (bRunning)
    {
        ofPushMatrix();
        ofTranslate(pos);
        ofRotateZ(rot);
        for (auto& t : texs)
            t.draw();
        ofPopMatrix();
    }
}

void Knives::goCircle()
{
    if (!bRunning)
    {
        bRunning = true;
        
        rot = ofRandom(360);
        pos.set(ofRandom(500, APP_W - 500), ofRandom(200, APP_H - 200));
        ofPoint center = ofPoint::zero();
        float fromRad = ofRandom(100, 200);
        vector<ofPoint> froms = getCircularPts(fromRad, center, texs.size());
        vector<ofPoint> interps = getCircularPts(fromRad + 50, center, texs.size());
        vector<ofPoint> tos = getCircularPts(1000, center, texs.size());
        for (int i = 0; i < texs.size(); i++)
            texs.at(i).goCircle(froms.at(i), interps.at(i), tos.at(i));
    }
}

void Knives::goLine()
{
    
}