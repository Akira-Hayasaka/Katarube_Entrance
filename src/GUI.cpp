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
    kinectGUI.setup("kinect", "settings/kinect.xml");
    kinectGUI.add(kinectAngle.setup("kinect head angle", 0.0, -30.0, 30.0));
    kinectGUI.add(kinectNearThresh.setup("depth thresh near cm", KINECT_MIN_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectGUI.add(kinectFarThresh.setup("depth thresh far cm", KINECT_MAX_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectGUI.add(contourMinArea.setup("contour min area", 10, 1, 100));
    kinectGUI.add(contourMaxArea.setup("contour max area", 200, 1, 500));
    kinectGUI.add(contourThreshold.setup("contour bri threshold", 128, 0, 255));
    kinectGUI.add(contourFindHole.setup("find hole", false));
    
    kinectAngle.addListener(&Global::kinect, &Kinect::onAngleChanged);
    kinectNearThresh.addListener(&Global::kinect, &Kinect::onNearThreshChanged);
    kinectFarThresh.addListener(&Global::kinect, &Kinect::onFarThreshChanged);
    contourMinArea.addListener(&Global::kinect, &Kinect::onContourMinAreaChanged);
    contourMaxArea.addListener(&Global::kinect, &Kinect::onContourMaxAreaChanged);
    contourThreshold.addListener(&Global::kinect, &Kinect::onContourBriThreshChanged);
    contourFindHole.addListener(&Global::kinect, &Kinect::onFindContourHoleChanged);
    
    kinectGUI.loadFromFile("settings/kinect.xml");
    
    kinectGUI.setSize(600, kinectGUI.getHeight());
    kinectGUI.setWidthElements(600);
}

void GUI::draw()
{
    if (!bHide)
        kinectGUI.draw();
}