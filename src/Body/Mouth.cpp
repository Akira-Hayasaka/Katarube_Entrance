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
    
    ofAddListener(Global::tickEvent, this, &Mouth::tick);
    
    bPlay = false;
    curFrame = 0;
    blendIdx = ofRandom(blendTexs.size()-1);
}

void Mouth::play()
{
    bPlay = true;
}

void Mouth::tick()
{
    if (bPlay)
    {
        curFrame++;
        blendIdx = ofRandom(blendTexs.size()-1);
        
        if (curFrame >= seq.size())
            curFrame = 0;
    }
}

void Mouth::draw(const ofTexture& bgMask, const ofTexture& bg)
{
    seqTweak.begin();
    seqTweak.setUniformTexture("blendTex", blendTexs.at(blendIdx), 1);
    seqTweak.setUniformTexture("bgMask", bgMask, 2);
    seqTweak.setUniformTexture("paperTex", bg, 3);
    seq.at(curFrame).draw(0, 0);
    seqTweak.end();
}