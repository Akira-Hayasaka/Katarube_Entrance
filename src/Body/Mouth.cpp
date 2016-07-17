//
//  Mouth.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Mouth.hpp"

void Mouth::setup(string seqDirPath, string blendDirPath)
{
    // - crop to roi
    // - chroma keying
    // - save it as tex vector
    
    float chromaThresh = 0.0;
    ofColor keyColor;
    ofxXmlSettings settings;
    settings.load(seqDirPath + "/settings.xml");
    settings.pushTag("roi");
    ofRectangle roi(settings.getValue("x", 0), settings.getValue("y", 0),
                    settings.getValue("w", 1920), settings.getValue("h", 1080));
    settings.popTag();
    settings.pushTag("chroma");
    chromaThresh = settings.getValue("thresh", 0.0);
    keyColor.set(settings.getValue("r", 0), settings.getValue("g", 0), settings.getValue("b", 0));
    settings.popTag();
    settings.clear();
    
	seqTweak.load("shaders/common/simpleVert.vert", "shaders/scene/seqTweak.frag");
    
    ofDirectory seqDir(seqDirPath);
    seqDir.listDir();
    for (int i = 0; i < seqDir.size(); i++)
    {
        ofFile f = seqDir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
        {
            ofFbo fbo;
            seq.push_back(fbo);
            ofTexture tex;
            ofLoadImage(tex, f.getAbsolutePath());
            seq.back().allocate(roi.getWidth(), roi.getHeight());
            seq.back().begin();
            ofClear(0);
            Global::chromaKey.begin();
            Global::chromaKey.setUniform3f("chromaKeyColor", ofVec3f(keyColor.r/255.0, keyColor.g/255.0, keyColor.b/255.0));
            Global::chromaKey.setUniform1f("threshold", chromaThresh);
            tex.drawSubsection(0, 0, roi.getWidth(), roi.getHeight(), roi.x, roi.y);
            Global::chromaKey.end();
            seq.back().end();
            tex.clear();
        }
    }
    seqDir.close();
    
    tweaker.allocate(roi.getWidth(), roi.getHeight());
    
    ofDirectory blendDir(blendDirPath);
    blendDir.listDir();
    for (int i = 0; i < blendDir.size(); i++)
    {
        ofFile f = blendDir.getFile(i);
        if (f.getExtension() == "jpg" || f.getExtension() == "png")
        {
            ofTexture t;
            blendTexs.push_back(t);
            ofLoadImage(blendTexs.back(), f.getAbsolutePath());
        }
    }
    blendDir.close();
    
    ofAddListener(Global::tickEvent, this, &Mouth::onTickEvent);
    ofAddListener(Global::eatEvent, this, &Mouth::onEatEvent);
    
    facePosOrig = ofPoint(-700, 0, 0);
    facePosDest = ofPoint::zero();
    curFacePos = facePosOrig;

    curFrame = 0;
    blendIdx = ofRandom(blendTexs.size()-1);
    state = NONE;
}

void Mouth::update()
{

}

void Mouth::draw()
{
    if (state == NONE)
        return;
    
    seqTweak.begin();
    seqTweak.setUniformTexture("tex0", tweaker.getTexture(), 0);
    seqTweak.setUniformTexture("blendTex", blendTexs.at(blendIdx), 1);
    drawPlane(tweaker.getWidth(), tweaker.getHeight());
    seqTweak.end();
}

void Mouth::genTweakTex()
{
    tweaker.begin();
    ofClear(0);
    seq.at(curFrame).draw(curFacePos);
    tweaker.end();
}

void Mouth::onTickEvent()
{
    if (state != NONE)
    {
        curFrame++;
        blendIdx = ofRandom(blendTexs.size()-1);
        
        if (state == EATING)
        {
            if (curFrame >= 26)
                Tweenzor::add(&curFacePos.x, curFacePos.x, facePosOrig.x, 0.0f, 0.6f, EASE_OUT_CUBIC);
        }
        
        if (curFrame >= seq.size())
        {
            curFrame = 0;
            state = NONE;
        }
        
        genTweakTex();
    }
}

void Mouth::onEatEvent()
{
    curFrame = 0;
    Tweenzor::add(&curFacePos.x, curFacePos.x, facePosDest.x, 0.0f, 0.5f, EASE_OUT_EXPO);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&curFacePos.x), this, &Mouth::onEndEmerge);
    genTweakTex();
    state = EMERGE;
}

void Mouth::onEndEmerge(float* arg)
{
    state = EATING;
}