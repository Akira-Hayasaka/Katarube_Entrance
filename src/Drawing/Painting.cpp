//
//  Painting.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/19/16.
//
//

#include "Painting.hpp"

void Painting::setup(string texPath, bool bNeedContour, bool bForPuppet)
{
    ofImage loader;
    loader.load(texPath);
    this->bNeedContour = bNeedContour;
    bContourReady = (bNeedContour) ? false : true;
    
    paintingID = genUUID();
    
    if (bForPuppet)
    {
        int maxDrawingH = 300;
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
            contourFinder.setThreshold(12);
            contourFinder.findContours(px);
            contourFinder.setSortBySize(true);
            contourFinder.setFindHoles(false);
        }
        outline = contourFinder.getPolylines();
        for (auto& l : outline)
            l.setClosed(true);
//        vector<cv::Point> pts = contourFinder.getConvexHull(0);
//        ofPolyline line;
//        for (auto p : pts)
//            line.addVertex(ofxCv::toOf(p));
//        outline.push_back(line);
        
        for (int i = 0; i < 5; i++)
        {
            contourFinder.setMinAreaRadius(10);
            contourFinder.setMaxAreaRadius(200);
            contourFinder.setThreshold(128);
            contourFinder.findContours(px);
            contourFinder.setFindHoles(true);
        }
        contourWHoles = contourFinder.getPolylines();
        if (bForPuppet)
        {
            for (auto& o : contourWHoles)
                o = o.getResampledBySpacing(20);
        }
        else
        {
            for (auto& o : contourWHoles)
                o = o.getResampledByCount(20);
        }
        ofSort(contourWHoles, compareLeft2Right);
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
    ofVec2f curScale(scale, scale);

    if (phase == END)
    {
        ofVec2f rdmPos(ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0));
        ofVec2f rdmScale(ofRandom(0.99, 1.01), ofRandom(0.99, 1.01));
        pos += rdmPos;
        curScale *= rdmScale;
    }
    
    if (bNeedContour)
    {
        if (phase == DRAWING)
        {
            ofPushMatrix();
            ofTranslate(pos.x + (tex.getWidth()/2 * (1.0 - curScale.x)),
                        pos.y + (tex.getHeight()/2 * (1.0 - curScale.y)));
            ofScale(curScale);
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
            ofTranslate(pos.x + (tex.getWidth()/2 * (1.0 - curScale.x)),
                        pos.y + (tex.getHeight()/2 * (1.0 - curScale.y)));
            ofScale(curScale);
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
            ofScale(curScale);
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
        for (auto l : contourWHoles)
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
        copy(contourWHoles.begin(), contourWHoles.end(), inserter(contourForProcess, contourForProcess.end()));
        ptsIdx = 0;
        
        utilFbo.begin();
        ofClear(0);
        utilFbo.end();
        
        ofPoint dest(pos + contourWHoles.front().getVertices().at(0));
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