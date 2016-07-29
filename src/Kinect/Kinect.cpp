//
//  Kinect.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/16/16.
//
//

#include "Kinect.hpp"

void Kinect::setup()
{
    ofxXmlSettings package;
    package.load("package.xml");
    bKinectConnected = ofToBool(package.getValue("kinectConnected", "true"));
    package.clear();
    
    if (bKinectConnected)
    {
        // this calculation uses some cpu, leave off if not needed
        device.setRegistration(true);
        
        device.init();
        device.open();
        
        if (device.isConnected())
        {
            ofLogNotice() << "sensor-emitter dist: " << device.getSensorEmitterDistance() << "cm";
            ofLogNotice() << "sensor-camera dist:  " << device.getSensorCameraDistance() << "cm";
            ofLogNotice() << "zero plane pixel size: " << device.getZeroPlanePixelSize() << "mm";
            ofLogNotice() << "zero plane dist: " << device.getZeroPlaneDistance() << "mm";
        }
    }
    else
    {
        fakeKinect.load("mov/debug/kinectTest.mov");
        fakeKinect.setLoopState(OF_LOOP_NORMAL);
        fakeKinect.play();
    }
    
    threshedTex.allocate(device.getWidth(), device.getHeight());
    depthThreshShader.load("shaders/common/simpleVert.vert", "shaders/kinect/threshDepth.frag");
    bInited = false;
}

void Kinect::update()
{
    if (bKinectConnected)
        device.update();
    else
        fakeKinect.update();
    
    storeDepthTex();
    threshDepthTex();
    makeContours();
}

bool Kinect::isInited()
{
    if (bKinectConnected)
        return device.isInitialized() && device.isConnected() && bInited;
    else
        return false;//bInited;
}

vector<ofPolyline> Kinect::getWarpedContour(ofMatrix4x4 warpMat)
{
    vector<ofPolyline> rtn;
    if (isInited())
    {
        for (int i = 0; i < contourFinder.size(); i++)
        {
            ofPolyline l = contourFinder.getPolyline(i);
            l.simplify();
            l = l.getResampledByCount(50);
            for (auto& p : l.getVertices())
                p = p * warpMat;
            rtn.push_back(l);
        }
    }
    return rtn;
}

void Kinect::drawContour(float x, float y, float w, float h)
{
    if (isInited())
    {
        ofPushMatrix();
        ofTranslate(x, y);
        ofScale(w/KINECT_W, h/KINECT_H);
        ofPushStyle();
        ofSetColor(ofColor::magenta);
        contourFinder.draw();
        ofPopStyle();
        ofPopMatrix();
    }
}

void Kinect::storeDepthTex()
{
    if (bKinectConnected)
    {
        if (device.isFrameNew())
        {
            depthTex = device.getDepthTexture();
            bInited = true;
        }
    }
    else
    {
        if (fakeKinect.isFrameNew())
        {
            depthTex = fakeKinect.getTexture();
            bInited = true;
        }
    }
}

void Kinect::threshDepthTex()
{
    if (isInited())
    {
        threshedTex.begin();
        ofClear(0);
        depthThreshShader.begin();
        depthThreshShader.setUniform1f("nearThresh", nearThresh);
        depthThreshShader.setUniform1f("farThresh", farThresh);
        depthThreshShader.setUniform1f("angleAdjust", angleAdjust);
        depthTex.draw(0, 0);
        depthThreshShader.end();
        threshedTex.end();
    }
}

void Kinect::makeContours()
{
    if (isInited())
    {
        contourSourcePx.clear();
        threshedTex.readToPixels(contourSourcePx);
        contourFinder.setMinAreaRadius(contourMinArea);
        contourFinder.setMaxAreaRadius(contourMaxArea);
        contourFinder.setThreshold(contourBriThresh);
        contourFinder.findContours(contourSourcePx);
        contourFinder.setFindHoles(bFindContourHole);
        contourTracker = contourFinder.getTracker();
    }
}