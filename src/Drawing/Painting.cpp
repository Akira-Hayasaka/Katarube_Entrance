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
    bContourReady = false;
    
    tex.allocate(loader.getWidth(), loader.getHeight());
    tex.begin();
    ofClear(0);
    loader.draw(0, 0);
    tex.end();
    
    contourPhase = NONE;
    ptsIdx = 0;
    
    if (bDrawWContour)
    {
        utilFbo.allocate(tex.getWidth(), tex.getHeight());
        utilFbo.begin();
        ofClear(0);
        Global::whitize.begin();
        tex.draw(0, 0);
        Global::whitize.end();
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
        
        ofAddListener(Global::gotContourEvent, this, &Painting::onGotContourEvent);
        ofNotifyEvent(Global::genContourEvent, cmdInfo);
    }
}

void Painting::update()
{
    if (bDrawWContour)
    {
        if (contourPhase == WAITINGHAND)
        {
            if (Global::ELAPSED_TIME - beginDrawWContourTime > waitHandDur)
                contourPhase = DRAWING;
        }
        else if (contourPhase == DRAWING)
        {
            ptsIdx++;
            if (ptsIdx >= contourForProcess.front().size())
            {
                ptsIdx = 0;
                contourForProcess.pop_front();
                if (contourForProcess.empty())
                {
                    contourPhase = END;
                    ofNotifyEvent(Global::handRetireEvent);
                    return;
                }
            }
            
            ofPoint p = contourForProcess.front().getVertices().at(ptsIdx);
            utilFbo.begin();
            ofPushStyle();
            ofSetRectMode(OF_RECTMODE_CENTER);
            Global::petip.draw(p);
            ofSetRectMode(OF_RECTMODE_CORNER);
            ofPopStyle();
            utilFbo.end();
            
            ofPoint dest(pos + p);
            ofNotifyEvent(Global::updateHandPosEvent, dest);
        }
    }
}

void Painting::draw()
{
    if (bDrawWContour)
    {
        if (contourPhase == DRAWING)
        {
            ofPushMatrix();
            ofTranslate(pos);
            ofRotate(rot);
            Global::strokeMask.begin();
            Global::strokeMask.setUniformTexture("stroke", utilFbo.getTexture(), 1);
            tex.draw(0, 0);
            Global::strokeMask.end();
            ofPopMatrix();
        }
        else if (contourPhase == END)
        {
            ofPushMatrix();
            ofTranslate(pos);
            ofRotate(rot);
            tex.draw(0, 0);
            ofPopMatrix();
        }
    }
    else
    {
        ofPushMatrix();
        ofTranslate(pos);
        ofRotate(rot);
        tex.draw(0, 0);
        ofPopMatrix();
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

void Painting::beginDrawWContour()
{
    if (bContourReady)
    {
        contourForProcess.clear();
        copy(outline.begin(), outline.end(), inserter(contourForProcess, contourForProcess.end()));
        ptsIdx = 0;    
        contourPhase = WAITINGHAND;
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        ofPoint dest(pos + outline.front().getVertices().at(0));
        ofNotifyEvent(Global::drawEvent, dest);
        
        beginDrawWContourTime = Global::ELAPSED_TIME;
        waitHandDur = 1.0;
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