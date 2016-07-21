//
//  Ink.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/11/16.
//
//

#include "Ink.hpp"

void Ink::setup()
{
    scrn.allocate(APP_W, APP_H);
    clearScrn();

#ifdef TARGET_WIN32
    canvasRatio = 2.0;
#else
	canvasRatio = 4.0;
#endif
    canvasW = APP_W / canvasRatio;
    canvasH = APP_H / canvasRatio;
    inkSim.setup(canvasW, canvasH);
    Globals::inkUniforms = inkSim.getUniformInfo();
    
    ofDirectory dir("imgs/ink");
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
    
    ofAddListener(Globals::inkEvent, this, &Ink::onInkEvent);
    ofAddListener(Globals::clearInkEvent, this, &Ink::onClearInkEvent);
    ofAddListener(Globals::fadeOutInkEvent, this, &Ink::onFadeOut);
}

void Ink::update()
{
    inkSim.update();
    
    scrn.begin();
    ofClear(255);
    ofPushMatrix();
    ofScale(canvasRatio, canvasRatio);
    inkSim.draw();
    ofPopMatrix();
    
    ofPushStyle();
    ofSetColor(ofColor::white, alpha);
    ofDrawRectangle(0, 0, scrn.getWidth(), scrn.getHeight());
    ofPopStyle();
    
    scrn.end();
}

void Ink::onInkEvent()
{
    alpha = 0.0;
    
    ofColor c = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
    int idx = ofRandom(texs.size());
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    float rdm = ofRandom(0.8, 4.5);
    inkSim.begin();
    ofPushMatrix();
    ofTranslate(ofRandom(300 / canvasRatio, APP_W / canvasRatio - 300 / canvasRatio),
                ofRandom(150 / canvasRatio, APP_H / canvasRatio - 150 / canvasRatio));
    ofRotateZ(ofRandom(360));
    ofScale(1,-1,1);
    ofPushStyle();
    ofSetColor(getInkColor(c.getHueAngle(), 255, ofRandom(150, 200)));
    texs.at(idx).draw(0, 0, texs.at(idx).getWidth() / pow(canvasRatio, rdm), texs.at(idx).getHeight() / pow(canvasRatio, rdm));
    ofPopStyle();
    ofPopMatrix();
    inkSim.end();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    inkSim.update();
}

void Ink::onClearInkEvent()
{
    inkSim.clear();
}

void Ink::clearScrn()
{
    scrn.begin();
    ofClear(255);
    scrn.end();
}

void Ink::onFadeOut()
{
    Tweenzor::add(&alpha, alpha, 255.0f, 0.0f, 1.5f, EASE_OUT_SINE);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&alpha), this, &Ink::onEndFadeOut);
}

void Ink::onEndFadeOut(float* arg)
{
    inkSim.clear();
    alpha = 0.0;
}