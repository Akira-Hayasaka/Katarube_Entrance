//
//  Painting.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/19/16.
//
//

#include "Painting.hpp"

void Painting::setup(string texPath, bool bDrawWContour)
{
    ofTexture loader;
    ofLoadImage(loader, texPath);
    this->bDrawWContour = bDrawWContour;
    bContourReady = (bDrawWContour) ? false : true;
    
    tex.allocate(loader.getWidth(), loader.getHeight());
    tex.begin();
    ofClear(0);
    loader.draw(0, 0);
    tex.end();
    
    phase = NONE;
    ptsIdx = 0;
    
    if (bDrawWContour)
    {
        utilFbo.allocate(tex.getWidth(), tex.getHeight());
        utilFbo.begin();
        ofClear(0);
        Globals::whitize.begin();
        tex.draw(0, 0);
        Globals::whitize.end();
        utilFbo.end();
        
        ofPixels px;
        utilFbo.readToPixels(px);
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        cmdID = genUUID();
        DrawCommandInfo cmdInfo;
        cmdInfo.cmdID = cmdID;
        cmdInfo.px = px;
        cmdInfo.contourMinArea = 10;//loader.getWidth() * loader.getHeight() * 0.5;
        cmdInfo.contourMaxArea = 200;//loader.getWidth() * loader.getHeight() * 1.5;
        cmdInfo.contourBriThresh = 128;
        
        ofAddListener(Globals::gotContourEvent, this, &Painting::onGotContourEvent);
        ofNotifyEvent(Globals::genContourEvent, cmdInfo);
    }
}

void Painting::update()
{
    if (bDrawWContour)
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
    if (bDrawWContour)
    {
        if (phase == DRAWING)
        {
            ofPushMatrix();
            ofTranslate(pos);
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
    if (bDrawWContour)
    {
        ofPushStyle();
        ofSetColor(ofColor::red);
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(rot);
        for (auto l : outline)
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
    
    if (bDrawWContour && bContourReady)
    {
        contourForProcess.clear();
        copy(outline.begin(), outline.end(), inserter(contourForProcess, contourForProcess.end()));
        ptsIdx = 0;
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        ofPoint dest(pos + outline.front().getVertices().at(0));
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

void Painting::onGotContourEvent(DrawCommandContour& cc)
{
    if (cc.cmdID == cmdID)
    {
        outline = cc.contours;
        for (auto& o : outline)
            o = o.getResampledByCount(20);
        ofSort(outline, compareLeft2Right);
        bContourReady = true;
    }
}