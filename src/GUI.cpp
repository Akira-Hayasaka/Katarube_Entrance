//
//  GUI.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/17/16.
//
//

#include "GUI.hpp"

void GUI::setup()
{
    // kinect device & contour gui
    kinectGUI.setup("kinect", "settings/kinect.xml");
    kinectGUI.add(kinectAngle.setup("kinect head angle", 0.0, -30.0, 30.0));
    kinectGUI.add(kinectNearThresh.setup("depth thresh near cm", KINECT_MIN_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectGUI.add(kinectFarThresh.setup("depth thresh far cm", KINECT_MAX_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectGUI.add(kinectAdjustAngle.setup("angle adjust", 0.0, -1.0, 1.0));
    kinectGUI.add(contourMinArea.setup("contour min area", 10, 1, 100));
    kinectGUI.add(contourMaxArea.setup("contour max area", 200, 1, 500));
    kinectGUI.add(contourThreshold.setup("contour bri threshold", 128, 0, 255));
    kinectGUI.add(contourFindHole.setup("find hole", false));
    
    kinectAngle.addListener(&Global::kinect, &Kinect::onAngleChanged);
    kinectNearThresh.addListener(&Global::kinect, &Kinect::onNearThreshChanged);
    kinectFarThresh.addListener(&Global::kinect, &Kinect::onFarThreshChanged);
    kinectAdjustAngle.addListener(&Global::kinect, &Kinect::onAngleAdjustChanged);
    contourMinArea.addListener(&Global::kinect, &Kinect::onContourMinAreaChanged);
    contourMaxArea.addListener(&Global::kinect, &Kinect::onContourMaxAreaChanged);
    contourThreshold.addListener(&Global::kinect, &Kinect::onContourBriThreshChanged);
    contourFindHole.addListener(&Global::kinect, &Kinect::onFindContourHoleChanged);
    
    kinectGUI.loadFromFile("settings/kinect.xml");
    
    kinectGUI.setSize(KINECT_W, kinectGUI.getHeight());
    kinectGUI.setWidthElements(KINECT_W);
    
    // proj warp
    ofVec2f tweakProjRes = ofVec2f(PROJ_W, PROJ_H) * WARP_TWEAK_SCALE;
    projWarpers.resize(NUM_PROJ);
    for (int i = 0; i < projWarpers.size(); i++)
    {
        ofPoint warpOrig = ofPoint(PROJ_W/2 - PROJ_W/2*WARP_TWEAK_SCALE + (PROJ_W - PROJ_W * WARP_TWEAK_SCALE)* i,
                                   PROJ_H/2 - PROJ_H/2*WARP_TWEAK_SCALE);
        projWarpers.at(i).setSourceRect(ofRectangle(0, 0, PROJ_W, PROJ_H));
        projWarpers.at(i).setTopLeftCornerPosition(ofPoint(warpOrig.x + tweakProjRes.x * i, warpOrig.y));
        projWarpers.at(i).setTopRightCornerPosition(ofPoint(warpOrig.x + tweakProjRes.x * i + tweakProjRes.x, warpOrig.y));
        projWarpers.at(i).setBottomLeftCornerPosition(ofPoint(warpOrig.x + tweakProjRes.x * i, warpOrig.y + tweakProjRes.y));
        projWarpers.at(i).setBottomRightCornerPosition(ofPoint(warpOrig.x + tweakProjRes.x * i + tweakProjRes.x, warpOrig.y + tweakProjRes.y));
        projWarpers.at(i).setup();
        projWarpers.at(i).load("settings/warps/projWarp" + ofToString(i) + ".xml");
        projWarpers.at(i).update();
        Global::projMats.at(i) = projWarpers.at(i).getMatEx();
    }
    
    // kinect warp
    ofVec2f tweakKinectRes = ofVec2f(KINECT_W, KINECT_H) * WARP_TWEAK_SCALE;
    ofPoint warpOrig = ofPoint(PROJ_W/2 - KINECT_W/2*WARP_TWEAK_SCALE, PROJ_H/2 - KINECT_H/2*WARP_TWEAK_SCALE);
    kinectWarper.setSourceRect(ofRectangle(0, 0, KINECT_W, KINECT_H));
    kinectWarper.setTopLeftCornerPosition(ofPoint(warpOrig.x, warpOrig.y));
    kinectWarper.setTopRightCornerPosition(ofPoint(warpOrig.x + tweakKinectRes.x, warpOrig.y));
    kinectWarper.setBottomLeftCornerPosition(ofPoint(warpOrig.x, warpOrig.y + tweakKinectRes.y));
    kinectWarper.setBottomRightCornerPosition(ofPoint(warpOrig.x + tweakKinectRes.x, warpOrig.y + tweakKinectRes.y));
    kinectWarper.setup();
    kinectWarper.load("settings/warps/kinectWarp.xml");
    kinectWarper.update();
    Global::kinectMat = kinectWarper.getMatEx();
    
    kinectFbo.allocate(KINECT_W, KINECT_H);
    kinectFbo.begin();
    ofClear(0);
    ofSetColor(ofColor::pink, 100);
    ofDrawRectangle(0, 0, kinectFbo.getWidth(), kinectFbo.getHeight());
    kinectFbo.end();
}

void GUI::update()
{
    if (!bHide)
    {
        int idx = 0;
        for (auto& warper : projWarpers)
        {
            warper.update();
            Global::projMats.at(idx) = warper.getMatEx();
            idx++;
        }
        
        kinectWarper.update();
        Global::kinectMat = kinectWarper.getMatEx();

        if (Global::kinect.isInited())
        {
            contours.clear();
            contourPaths.clear();
            
            // get warped contour
            contours = Global::kinect.getContourInfo(Global::kinectMat);
            
            kinectFbo.begin();
            ofClear(0);
            Global::kinect.getDepthTexture().draw(0, 0);
            kinectFbo.end();
            
            for (auto& c : contours)
            {
                int idx = 0;
                ofPath path;
                for (auto& p : c.getVertices())
                {
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
                path.simplify();
                path.setFillColor(ofColor::yellow);
                contourPaths.push_back(path);
            }
        }
    }
}

void GUI::draw()
{
    if (!bHide)
    {
        // draw warped kinect depth & contour
        if (Global::kinect.isInited())
        {
            ofPushMatrix();
            ofMultMatrix(Global::kinectMat);
            kinectFbo.draw(0, 0);
            ofPopMatrix();
            
            ofPushStyle();
            ofFill();
            for (auto c : contourPaths)
                c.draw();
            ofPopStyle();
        }
        
        // proj warpers
        ofPushStyle();
        for (auto warper : projWarpers)
        {
            ofSetColor(ofColor::magenta);
            warper.drawQuadOutline();
            
            ofSetColor(ofColor::yellow);
            warper.drawCorners();
            
            ofSetColor(ofColor::magenta);
            warper.drawHighlightedCorner();
            
            ofSetColor(ofColor::red);
            warper.drawSelectedCorner();
        }
        
        // kinect warper
        ofSetColor(ofColor::magenta.getInverted());
        kinectWarper.drawQuadOutline();
        
        ofSetColor(ofColor::yellow.getInverted());
        kinectWarper.drawCorners();
        
        ofSetColor(ofColor::magenta.getInverted());
        kinectWarper.drawHighlightedCorner();
        
        ofSetColor(ofColor::red.getInverted());
        kinectWarper.drawSelectedCorner();

        ofPopStyle();
        
        // draw kinect tex for gui
        if (Global::kinect.isInited())
        {
            int margin = 4;
            ofPoint p = kinectGUI.getPosition();
            p.y += kinectGUI.getHeight(); + margin;
            ofPushStyle();
            ofSetColor(ofColor::gray);
            ofDrawRectangle(p.x, p.y, kinectGUI.getWidth(), KINECT_H/2);
            ofPopStyle();
            Global::kinect.getDepthTexture().draw(p.x + margin/2, p.y + margin/2, KINECT_W/2 - margin, KINECT_H/2 - margin);
            Global::kinect.getThreshedTexture().draw(p.x + KINECT_W/2 + margin/2, p.y + margin/2, KINECT_W/2 - margin, KINECT_H/2 - margin);
            Global::kinect.drawContour(p.x + KINECT_W/2 + margin/2, p.y + margin/2, KINECT_W/2 - margin, KINECT_H/2 - margin);
        }
        
        kinectGUI.draw();
    }
}

void GUI::saveProjWarp()
{
    for (int i = 0; i < projWarpers.size(); i++)
        projWarpers.at(i).save("settings/warps/projWarp" + ofToString(i) + ".xml");
}

void GUI::saveKinectWarp()
{
    kinectWarper.save("settings/warps/kinectWarp.xml");
}