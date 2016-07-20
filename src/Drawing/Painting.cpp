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
//    ofTexture loader;
    ofLoadImage(loader, texPath);
    this->bDrawWContour = bDrawWContour;
    bContourReady = false;
    
//    tex.allocate(loader.getWidth(), loader.getHeight());
//    tex.begin();
//    ofClear(0);
//    loader.draw(0, 0);
//    tex.end();
    
    contourPhase = NONE;
    ptsIdx = 0;
    
//    if (bDrawWContour)
//    {
//        utilFbo.allocate(tex.getWidth(), tex.getHeight());
//        utilFbo.begin();
//        ofClear(0);
//        Global::whitize.begin();
//        tex.draw(0, 0);
//        Global::whitize.end();
//        utilFbo.end();
//        
//        ofPixels px;
//        utilFbo.readToPixels(px);
//        
//        px.mirror(true, false);
//
////        ofImage img;
////        img.setFromPixels(px);
////        tex.begin();
////        ofClear(0);
////        img.draw(0, 0);
////        tex.end();
//        
//        utilFbo.begin();
//        ofClear(0);
//        utilFbo.end();
//        
//        cmdID = genUUID();
//        DrawCommandInfo cmdInfo;
//        cmdInfo.cmdID = cmdID;
//        cmdInfo.px = px;
//        cmdInfo.contourMinArea = 10;//loader.getWidth() * loader.getHeight() * 0.5;
//        cmdInfo.contourMaxArea = 200;//loader.getWidth() * loader.getHeight() * 1.5;
//        cmdInfo.contourBriThresh = 128;
//        
//        ofAddListener(Global::gotContourEvent, this, &Painting::onGotContourEvent);
//        ofNotifyEvent(Global::genContourEvent, cmdInfo);
//    }
}

void Painting::update()
{
//    if (bDrawWContour)
//    {
//        if (contourPhase == DRAWING)
//        {
//            ptsIdx++;
//            if (ptsIdx >= contourForProcess.front().size())
//            {
//                ptsIdx = 0;
//                contourForProcess.pop_front();
//                if (contourForProcess.empty())
//                {
//                    contourPhase = END;
//                    return;
//                }
//            }
//            
//            ofPoint p = contourForProcess.front().getVertices().at(ptsIdx);
//            utilFbo.begin();
//            ofPushStyle();
//            ofSetRectMode(OF_RECTMODE_CENTER);
//            Global::petip.draw(p);
//            ofSetRectMode(OF_RECTMODE_CORNER);
//            ofPopStyle();
//            utilFbo.end();
//        }
//    }
}

void Painting::draw()
{
    if (bDrawWContour)
    {
//        Global::strokeMask.begin();
//        Global::strokeMask.setUniformTexture("stroke", utilFbo.getTexture(), 1);
//        ofPushMatrix();
//        ofTranslate(pos.x, pos.y + tex.getHeight());
//        ofRotate(rot);
//        tex.draw(0, 0);
//        ofPopMatrix();
//        Global::strokeMask.end();
        
        ofPushMatrix();
        ofTranslate(500, 300);
        ofRotate(rot);
        loader.draw(0, 0);
        ofPopMatrix();
        
//        utilFbo.draw(500, 500);
    }
    else
    {
        ofPushMatrix();
        ofTranslate(pos.x, pos.y + tex.getHeight());
        ofRotate(rot);
        ofScale(1,-1,1);
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
        contourPhase = DRAWING;
    }
}

void Painting::onGotContourEvent(DrawCommandContour& cc)
{
    if (cc.cmdID == cmdID)
    {
        outline = cc.contours;
        bContourReady = true;
    }
}