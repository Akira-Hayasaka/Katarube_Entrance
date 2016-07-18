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
    stopMotionContent.allocate(APP_W, APP_H);
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
    Global::b2dEdge = b2dEdge;
    
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
            Global::bottomLineAndAngs.push_back(ba);
        }
    }
    
    mouth.setup("imgs/body/mouth/1");
    drawingHand.setup("imgs/body/hand/drawing");
    fetchingHand.setup("imgs/body/hand/fetching");
    puttingHand.setup("imgs/body/hand/putting");
    ink.setup();
    cutout.setup();
    drawer.setup();
    
    ofAddListener(Global::tickEvent, this, &Content::onTickEvent);
}

void Content::update()
{
    mouth.update();
    drawingHand.update();
    fetchingHand.update();
    puttingHand.update();
    ink.update();
    cutout.update();
    drawer.update();
}

void Content::genFullScreenContent()
{
    fullScreenResult.begin();
    ofClear(0);
    
    blendOutput.begin();
    blendOutput.setUniformTexture("body", stopMotionContent.getTexture(), 0);
    blendOutput.setUniformTexture("ink", ink.getTexture(), 1);
    blendOutput.setUniformTexture("cutout", cutout.getTexture(), 2);
    blendOutput.setUniformTexture("bg", bg.getTexture(), 3);
    blendOutput.setUniformTexture("bgMask", bgMask.getTexture(), 4);
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
}

void Content::onTickEvent()
{
     // draw every stop motion content here
    stopMotionContent.begin();
    ofClear(0);
    drawer.draw();
    mouth.draw();
    drawingHand.draw();
    fetchingHand.draw();
    puttingHand.draw();
    stopMotionContent.end();
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