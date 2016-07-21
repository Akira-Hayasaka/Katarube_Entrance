//
//  Painting.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/19/16.
//
//

#include "Painting.hpp"

void Painting::setup(string texPath, bool bNeedContour, bool bConstrainSize)
{
    ofImage loader;
    loader.load(texPath);
    this->bNeedContour = bNeedContour;
    bContourReady = (bNeedContour) ? false : true;
    
    paintingID = genUUID();
    
    if (bConstrainSize)
    {
        int maxDrawingH = 400;
        float ratio = maxDrawingH / loader.getHeight();
        loader.resize(loader.getWidth() * ratio, loader.getHeight() * ratio);
    }
    
    tex.allocate(loader.getWidth(), loader.getHeight());
    tex.begin();
    ofClear(0);
    loader.draw(0, 0);
    tex.end();
    
    phase = NONE;
    ptsIdx = 0;
    
    if (bNeedContour)
    {
        utilFbo.allocate(tex.getWidth(), tex.getHeight());
        utilFbo.begin();
        ofClear(0);
        Globals::whitize.begin();
        tex.draw(0, 0);
        Globals::whitize.end();
        utilFbo.end();
        
        utilFbo.readToPixels(px);
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        // try 5 times
        ofxCv::ContourFinder contourFinder;
        for (int i = 0; i < 5; i++)
        {
            contourFinder.setMinAreaRadius(10);
            contourFinder.setMaxAreaRadius(200);
            contourFinder.setThreshold(128);
            contourFinder.findContours(px);
            contourFinder.setFindHoles(false);
        }
        
        outlineOriginal = contourFinder.getPolylines();
        outlineSimplified = outlineOriginal;
        for (auto& o : outlineSimplified)
            o = o.getResampledByCount(20);
        ofSort(outlineSimplified, compareLeft2Right);
        bContourReady = true;
    }
}

void Painting::update()
{
    if (bNeedContour)
    {
        if (phase == WAITINGHAND)
        {
            if (Globals::ELAPSED_TIME - beginDrawWContourTime > waitHandDur)
                phase = DRAWING;
        }
        else if (phase == DRAWING)
        {
            ptsIdx++;
            if (ptsIdx >= contourForProcess.front().size())
            {
                ptsIdx = 0;
                contourForProcess.pop_front();
                if (contourForProcess.empty())
                {
                    phase = END;
                    ofNotifyEvent(Globals::handRetireEvent);
                    return;
                }
            }
            
            ofPoint p = contourForProcess.front().getVertices().at(ptsIdx);
            utilFbo.begin();
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            Globals::petip.draw(p);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopStyle();
            utilFbo.end();
            
            ofPoint dest(pos + p);
            ofNotifyEvent(Globals::updateHandPosEvent, dest);
        }
    }
    else
    {
        if (phase == WAITINGHAND)
        {
            if (Globals::ELAPSED_TIME - beginDrawWContourTime > waitHandDur)
                phase = DRAWING;
        }
        else if (phase == DRAWING)
        {
            phase = END;
        }
    }
}

void Painting::draw()
{
    if (bNeedContour)
    {
        if (phase == DRAWING)
        {
            ofPushMatrix();
            ofTranslate(pos.x + (tex.getWidth()/2 * (1.0 -scale)),
                        pos.y + (tex.getHeight()/2 * (1.0 - scale)));
            ofScale(scale, scale);
            ofRotate(rot);
            Globals::strokeMask.begin();
            Globals::strokeMask.setUniformTexture("stroke", utilFbo.getTexture(), 1);
            tex.draw(0, 0);
            Globals::strokeMask.end();
            ofPopMatrix();
        }
        else if (phase == END)
        {
            ofPushMatrix();
            ofTranslate(pos.x + (tex.getWidth()/2 * (1.0 -scale)),
                        pos.y + (tex.getHeight()/2 * (1.0 - scale)));
            ofScale(scale, scale);
            ofRotate(rot);
            tex.draw(0, 0);
            ofPopMatrix();
        }
    }
    else
    {
        if (phase == DRAWING || phase == END)
        {
            ofSetRectMode(OF_RECTMODE_CENTER);
            ofPushMatrix();
            ofTranslate(pos);
            ofScale(scale, scale);
            ofRotate(rot);
            tex.draw(0, 0);
            ofPopMatrix();
            ofSetRectMode(OF_RECTMODE_CORNER);
        }
    }
}

void Painting::drawOutline()
{
    if (bNeedContour)
    {
        ofPushStyle();
        ofSetColor(ofColor::red);
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(rot);
        for (auto l : outlineSimplified)
            l.draw();
        ofPopMatrix();
        ofPopStyle();
    }
}

void Painting::fadeOut()
{
    Tweenzor::add(&scale, scale, 0.0f, 0.0f, 1.0f, EASE_OUT_SINE);
}

void Painting::beginDraw()
{
    scale = 1.0;
    beginDrawWContourTime = Globals::ELAPSED_TIME;
    phase = WAITINGHAND;
    
    if (bNeedContour && bContourReady)
    {
        contourForProcess.clear();
        copy(outlineSimplified.begin(), outlineSimplified.end(), inserter(contourForProcess, contourForProcess.end()));
        ptsIdx = 0;
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        ofPoint dest(pos + outlineSimplified.front().getVertices().at(0));
        ofNotifyEvent(Globals::drawEvent, dest);
        
        waitHandDur = 1.0;
    }
    else
    {
        ofPoint dest(pos.x - tex.getWidth()/2, pos.y - tex.getHeight()/2);
        ofNotifyEvent(Globals::putEvent, dest);
        waitHandDur = 0.5;
    }
}