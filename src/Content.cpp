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
    interactionContour.allocate(APP_W/3, APP_H/3);
    bg.allocate(APP_W, APP_H);
    bgMask.allocate(APP_W, APP_H);
    blendOutput.load("shaders/common/simpleVert.vert", "shaders/scene/blendOutput.frag");
    
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
    ofxCv::ContourFinder contourFinder;
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
    
    ofPolyline topLine, btmLine;
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
        if (fabs(ang) > 170.0)
            topLine.addVertex(b2dEdge.getVertices().at(i));
    }
    
    Globals::box2dBBox.resize(2);
    Globals::box2dBBox.at(0) = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    Globals::box2dBBox.at(0)->addVertexes(topLine);
    Globals::box2dBBox.at(0)->setPhysics(0.0, 0.5, 0.5);
    Globals::box2dBBox.at(0)->create(Globals::box2d.getWorld());
    Globals::box2dBBox.at(1) = ofPtr<ofxBox2dEdge>(new ofxBox2dEdge);
    Globals::box2dBBox.at(1)->addVertexes(btmLine);
    Globals::box2dBBox.at(1)->setPhysics(0.0, 0.5, 0.5);
    Globals::box2dBBox.at(1)->create(Globals::box2d.getWorld());

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
    
    ofAddListener(Globals::tickEvent, this, &Content::onTickEvent);
}

void Content::update()
{
    body.update();
    ink.update();
    cutout.update();
    drawer.update();
    
    // update interaction contour(body & kinect) every frame
    updateInteractionContour();
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
        blendOutput.setUniform1f("doRdmForInteractive", 1.0);
    else
        blendOutput.setUniform1f("doRdmForInteractive", 0.0);
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

void Content::drawInteractionContour()
{
    interactionContour.draw(0, 0, APP_W, APP_H);
}

void Content::onTickEvent()
{
     // draw every stop motion content here
    outOfCanvasContent.begin();
    ofClear(0);
    body.draw();
    outOfCanvasContent.end();
    
    interactiveContent.begin();
    ofClear(255);
    drawer.draw();
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

void Content::updateInteractionContour()
{
    interactionContour.begin();
    ofClear(0);
    outOfCanvasContent.draw(0, 0, interactionContour.getWidth(), interactionContour.getHeight());
    interactionContour.end();
}