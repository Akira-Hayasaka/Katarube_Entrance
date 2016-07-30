//
//  Content.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Content.hpp"

void Content::setup()
{
    fullScreenResult.allocate(APP_W, APP_H);
    outOfCanvasContent.allocate(APP_W, APP_H);
    interactiveContent.allocate(APP_W, APP_H);
    interactionSource.allocate(APP_W/interactionSourceRatio, APP_H/interactionSourceRatio);
    bg.allocate(APP_W, APP_H);
    bgMask.allocate(APP_W, APP_H);
    contoutMask.allocate(APP_W, APP_H);
    blendOutput.load("shaders/common/simpleVert.vert", "shaders/scene/blendOutput.frag");
    
    interactionSource.begin();
    ofClear(0);
    interactionSource.end();
    
    contoutMask.begin();
    ofClear(0);
    contoutMask.end();
    
    ofTexture bg_s;
    ofTexture bgMask_s;
    ofLoadImage(bg_s, "imgs/common/bg_2.png");
    ofLoadImage(bgMask_s, "imgs/common/bgMask_2.png");
    
    bg.begin();
    ofClear(0);
    bg_s.draw(0, 0);
    bg.end();
    
    bgMask.begin();
    ofClear(0);
    bgMask_s.draw(0, 0);
    bgMask.end();
    
    ofTexture b2dEdgeTex;
    ofLoadImage(b2dEdgeTex, "imgs/common/b2d_edge_2.png");
    fullScreenResult.begin();
    ofClear(0);
    b2dEdgeTex.draw(0, 0);
    fullScreenResult.end();
    ofPixels b2dEdgePx;
    fullScreenResult.readToPixels(b2dEdgePx);
    fullScreenResult.begin();
    ofClear(0);
    fullScreenResult.end();
    
    // try 5 times
    for (int i = 0; i < 5; i++)
    {
        contourFinder.setMinAreaRadius(0);
        contourFinder.setMaxAreaRadius(10000);
        contourFinder.setThreshold(128);
        contourFinder.findContours(b2dEdgePx);
        contourFinder.setFindHoles(false);
    }
    b2dEdge = contourFinder.getPolyline(0);
    b2dEdge = b2dEdge.getResampledByCount(200);
    Globals::b2dEdge = b2dEdge;
    
    ofPolyline btmLine;
    for (int i = 0; i < b2dEdge.getVertices().size(); i++)
    {
        ofVec2f perp;
        if (i == b2dEdge.getVertices().size()-1)
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(0)).getPerpendicular();
        else
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(i+1)).getPerpendicular();
        float ang = ofVec2f(0, -1).angle(perp);
        
        if (fabs(ang) < 10.0)
            btmLine.addVertex(b2dEdge.getVertices().at(i));
    }
    
    Globals::box2dBBox.resize(1);
    Globals::box2dBBox.at(0) = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    Globals::box2dBBox.at(0)->addVertexes(btmLine);
    Globals::box2dBBox.at(0)->setPhysics(0.0, 0.5, 0.5);
    Globals::box2dBBox.at(0)->create(Globals::box2d->getWorld());

    for (int i = 0; i < b2dEdge.getVertices().size(); i++)
    {
        ofVec2f perp;
        if (i == b2dEdge.getVertices().size()-1)
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(0)).getPerpendicular();
        else
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(i+1)).getPerpendicular();
        
        float ang = ofVec2f(0, -1).angle(perp);
        if (fabs(ang) < 90)
        {
            BottomLineAndAng ba;
            ba.p = b2dEdge.getVertices().at(i);
            ba.ang = ang;
            Globals::bottomLineAndAngs.push_back(ba);
        }
    }
    
    body.setup();
    ink.setup();
    cutout.setup();
    drawer.setup();
    
    contourShader.load("shaders/common/simpleVert.vert", "shaders/scene/contour.frag");
    
    ofAddListener(Globals::tickEvent, this, &Content::onTickEvent);
}

void Content::update()
{
    body.update();
    ink.update();
    cutout.update();
    drawer.update();
    
    // update interaction contour (body & kinect) every frame
    if (Globals::curAppState == "INTERACTION")
        updateinteractionSource();
}

void Content::genFullScreenContent()
{
    fullScreenResult.begin();
    ofClear(0);
    
    blendOutput.begin();
    blendOutput.setUniformTexture("body", outOfCanvasContent.getTexture(), 0);
    blendOutput.setUniformTexture("ink", ink.getTexture(), 1);
    blendOutput.setUniformTexture("cutout", cutout.getTexture(), 2);
    blendOutput.setUniformTexture("interactive", interactiveContent.getTexture(), 3);
    blendOutput.setUniformTexture("bg", bg.getTexture(), 4);
    blendOutput.setUniformTexture("bgMask", bgMask.getTexture(), 5);
    if (Globals::curAppState == "INTERACTION")
        blendOutput.setUniform1f("doInteractive", 1.0);
    else
        blendOutput.setUniform1f("doInteractive", 0.0);
    blendOutput.setUniform3f("rdmForInteractive", ofRandom(-0.02, 0.02), ofRandom(-0.02, 0.02), ofRandom(-0.02, 0.02));
    blendOutput.setUniform2f("res", APP_W, APP_H);
    drawPlane(APP_W, APP_H);
    blendOutput.end();
    
    fullScreenResult.end();
}

void Content::drawLeft()
{
    fullScreenResult.getTexture().drawSubsection(0, 0, PROJ_W, PROJ_H, 0, 0);
}

void Content::drawRight()
{
    fullScreenResult.getTexture().drawSubsection(0, 0, PROJ_W, PROJ_H, PROJ_W, 0);
}

void Content::drawB2DEdge()
{
    ofPushStyle();
    ofSetColor(ofColor::cyan);
    b2dEdge.draw();
    for (int i = 0; i < b2dEdge.getVertices().size(); i++)
    {
        ofSetColor(ofColor::green);
        ofVec2f from, to, perp;
        from = b2dEdge.getVertices().at(i);
        if (i == b2dEdge.getVertices().size()-1)
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(0)).getPerpendicular();
        else
            perp = ofVec2f(b2dEdge.getVertices().at(i) - b2dEdge.getVertices().at(i+1)).getPerpendicular();
        to = b2dEdge.getVertices().at(i) + perp * 200;
        ofDrawLine(from, to);
        
        float ang = ofVec2f(0, -1).angle(perp);
        ofSetColor(ofColor::white);
        ofDrawBitmapStringHighlight(ofToString(ang, 2), from.getMiddle(to));
    }
    ofSetColor(ofColor::red);
    for (auto p : b2dEdge.getVertices())
        ofDrawCircle(p, 4);
    ofPopStyle();
    
    ofPushMatrix();
    ofScale(0.5, 0.5);
    ofPushStyle();
    ofSetColor(ofColor::red);
    for (auto bb : Globals::box2dBBox)
        bb->draw();
    ofPopStyle();
    ofPopMatrix();
}

void Content::drawinteractionContours()
{
//    interactionSource.draw(0, 0, APP_W, APP_H);
//    
//    ofPushStyle();
//    ofColor c = ofColor::red;
//    int i = 0;
//    for (auto pl : interactionContours)
//    {
//        c.setHueAngle(ofMap(i, 0, interactionContours.size(), 0, 360));
//        ofPushStyle();
//        ofSetColor(c);
//        pl.draw();
//        ofPopStyle();
//        i++;
//    }
//    ofPopStyle();
//    
//    interactionSource.draw(0, 0, PROJ_W, PROJ_H / 2);
//    
//    ofPushMatrix();
//    ofScale(interactionSource.getWidth() / PROJ_W, interactionSource.getHeight() / (PROJ_H / 2));
//    ofPushStyle();
//    c = ofColor::red;
//    i = 0;
//    for (auto pl : interactionContours)
//    {
//        c.setHueAngle(ofMap(i, 0, interactionContours.size(), 0, 360));
//        ofPushStyle();
//        ofSetColor(c);
//        pl.draw();
//        ofPopStyle();
//        i++;
//    }
//    ofPopStyle();
//    ofPopMatrix();
    
    ofPushStyle();
    ofColor c = ofColor::red;
    int i = 0;
    for (auto pl : interactionContours)
    {
        c.setHueAngle(ofMap(i, 0, interactionContours.size(), 0, 360));
        ofPushStyle();
        ofSetColor(c);
        pl.draw();
        ofPopStyle();
        i++;
    }
    ofPopMatrix();
    
    contoutMask.draw(0, 0);
}

void Content::onTickEvent()
{
    blendIdx = ofRandom(Globals::bodyBlendTexs.size()-1);
    
     // draw every stop motion content here
    outOfCanvasContent.begin();
    ofClear(0);
    body.draw();
    outOfCanvasContent.end();
    
    interactiveContent.begin();
    ofClear(255);
    drawer.draw();
    
    contourShader.begin();
    contourShader.setUniformTexture("tex", Globals::bodyBlendTexs.at(blendIdx), 0);
    contourShader.setUniformTexture("mask", contoutMask.getTexture(), 1);
    contourShader.setUniform2f("appRes", APP_W, APP_H);
    contourShader.setUniform2f("texRes", Globals::bodyBlendTexs.at(blendIdx).getWidth(), Globals::bodyBlendTexs.at(blendIdx).getHeight());
    drawPlane(APP_W, APP_H);
    contourShader.end();
    
    interactiveContent.end();
}

void Content::saveScreen()
{
    fullScreenResult.begin();
    ofClear(0);
    bg.draw(0, 0);
    fullScreenResult.end();
    
    ofPixels px;
    fullScreenResult.readToPixels(px);
    ofSaveImage(px, "imgs/saved/bg.png");
    
    fullScreenResult.begin();
    ofClear(0);
    bgMask.draw(0, 0);
    fullScreenResult.end();
    
    fullScreenResult.readToPixels(px);
    ofSaveImage(px, "imgs/saved/bgMask.png");
}

void Content::updateinteractionSource()
{
    vector<ofPolyline> kinectContours  = Globals::kinect.getContour();
    contourPaths.clear();
    for (auto& c : kinectContours)
    {
        int idx = 0;
        ofPath path;
        for (auto& p : c.getVertices())
        {
			p /= interactionSourceRatio;
            if (idx == 0)
            {
                path.newSubPath();
                path.moveTo(p);
            }
            else
            {
                path.lineTo(p);
            }
            idx++;
        }
        path.close();
        path.setFillColor(ofColor::white);
        contourPaths.push_back(path);
    }
    
    interactionSource.begin();
    ofClear(0);
    ofPushStyle();
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    ofPushMatrix();
    ofTranslate(Globals::leftKinectTrans.pos);
    ofScale(Globals::leftKinectTrans.scale, Globals::leftKinectTrans.scale);
    ofRotateZ(Globals::leftKinectTrans.ang);
    for (auto c : contourPaths)
        c.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(Globals::rightKinectTrans.pos);
    ofScale(Globals::rightKinectTrans.scale, Globals::rightKinectTrans.scale);
    ofRotateZ(Globals::rightKinectTrans.ang);
    for (auto c : contourPaths)
        c.draw();
    ofPopMatrix();
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofPopStyle();
    interactionSource.end();
    
    ofPixels interactionPx;
    interactionSource.readToPixels(interactionPx);
    
    interactionContours.clear();
    contourFinder.setMinAreaRadius(10);
    contourFinder.setMaxAreaRadius(1000);
    contourFinder.setThreshold(128);
    contourFinder.setSimplify(true);
    contourFinder.findContours(interactionPx);
    contourFinder.setFindHoles(false);
    interactionContours = contourFinder.getPolylines();
    
    interactionContourObjs.clear();
    contourPaths.clear();
    int idx = 0;
    for (auto& c : interactionContours)
    {
        c = c.getResampledBySpacing(10);
        c = c.getSmoothed(10);
        c.setClosed(true);
        
        if (c.size() > 5)
        {
            int idx = 0;
            ofPath path;
            for (auto& p : c.getVertices())
            {
                // scale up contours
                p *= APP_W / interactionSource.getWidth() * 2;
                
                if (idx == 0)
                {
                    path.newSubPath();
                    path.moveTo(p);
                }
                else
                {
                    path.lineTo(p);
                }
                idx++;
            }
            path.close();
            path.setFillColor(ofColor::white);
            contourPaths.push_back(path);
            
            ofPtr<ofxBox2dPolygon> contourObj = ofPtr<ofxBox2dPolygon>(new ofxBox2dPolygon);
            contourObj->addVertices(c.getVertices());
            contourObj->triangulatePoly();
            contourObj->create(Globals::box2d->getWorld());
            contourObj->setPhysics(10.0, 0.3, 0.3);
            interactionContourObjs.push_back(contourObj);
        }
        idx++;
    }
    
    contoutMask.begin();
    ofClear(0);
    for (auto p : contourPaths)
        p.draw();
    contoutMask.end();
}