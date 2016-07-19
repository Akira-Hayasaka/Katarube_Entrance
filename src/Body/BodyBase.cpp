//
//  BodyBase.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/18/16.
//
//

#include "BodyBase.hpp"

void BodyBase::setup(string seqDirPath)
{
    // - crop to roi
    // - chroma keying
    // - save it as tex vector
    
    float chromaThresh = 0.0;
    ofColor keyColor;
    ofxXmlSettings settings;
    settings.load(seqDirPath + "/settings.xml");
    settings.pushTag("roi");
    roi.set(settings.getValue("x", 0), settings.getValue("y", 0),
            settings.getValue("w", 1920), settings.getValue("h", 1080));
    settings.popTag();
    settings.pushTag("chroma");
    chromaThresh = settings.getValue("thresh", 0.0);
    keyColor.set(settings.getValue("r", 0), settings.getValue("g", 0), settings.getValue("b", 0));
    settings.popTag();
    settings.pushTag("anchor");
    anchor.x = settings.getValue("x", 0);
    anchor.y = settings.getValue("y", 0);
    settings.popTag();
    settings.clear();
    
    seqTweak.load("shaders/common/simpleVert.vert", "shaders/scene/seqTweak.frag");
    
    ofDirectory seqDir(seqDirPath);
    seqDir.listDir();
    for (int i = 0; i < seqDir.size(); i++)
    {
        ofFile f = seqDir.getFile(i);
        if (isImgFile(f.getExtension()))
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
//            seq.back().setAnchorPoint(anchor.x, anchor.y);
            tex.clear();
        }
    }
    seqDir.close();
    
    tweaker.allocate(roi.getWidth(), roi.getHeight());
}

void BodyBase::draw(BodyState bodyState)
{
    if (bodyState.state == BodyState::NONE)
        return;
    
    draw(bodyState, false, 0.0);
}

void BodyBase::draw(BodyState bodyState, bool bFromUpper, float ang)
{
    if (bodyState.state == BodyState::NONE)
        return;
    
    genTweakTex(bodyState);
    
    ofPushMatrix();
    if (bFromUpper)
    {
        ofTranslate(bodyState.curPos - anchor);
        ofRotateZ((bFromUpper) ? 180 + ang : 0 + ang);
    }
    else
    {
        ofTranslate(bodyState.curPos);
        ofRotateZ(ang);
        ofTranslate(-anchor);   
    }
    seqTweak.begin();
    seqTweak.setUniformTexture("tex0", tweaker.getTexture(), 0);
    seqTweak.setUniformTexture("blendTex", Global::bodyBlendTexs.at(bodyState.blendIdx), 1);
    drawPlane(tweaker.getWidth(), tweaker.getHeight());
    seqTweak.end();
    ofPopMatrix();
}

void BodyBase::genTweakTex(BodyState bodyState)
{
    tweaker.begin();
    ofClear(0);
    seq.at(bodyState.curFrame).draw(0, 0);
    tweaker.end();
}