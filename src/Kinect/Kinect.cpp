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
    
    threshedTex.allocate(device.getWidth(), device.getHeight());
    depthThreshShader.load("shaders/common/simpleVert.vert", "shaders/kinect/threshDepth.frag");
    
    bInited = false;
}

void Kinect::update()
{
    device.update();
    storeDepthTex();
    threshDepthTex();
    makeContours();
}

void Kinect::drawContour()
{
    if (isInited())
    {
        contourFinder.draw();
    }
}

void Kinect::storeDepthTex()
{
    if (device.isFrameNew())
    {
        depthTex = device.getDepthTexture();
        bInited = true;
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