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
    Global::inkUniforms = inkSim.getUniformInfo();
    
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
    
    ofAddListener(Global::inkEvent, this, &Ink::onInkEvent);
    ofAddListener(Global::clearInkEvent, this, &Ink::onClearInkEvent);
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
    scrn.end();
}

void Ink::onInkEvent()
{
//    inkSim.getUniformInfo()->waterAmount = ofRandom(0.1, 1.7);
    
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
