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
    kinectGUI.add(kinectAngle.setup("angle", 0.0, -30.0, 30.0));
    kinectGUI.add(kinectNearThresh.setup("near (cm)", KINECT_MIN_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectGUI.add(kinectFarThresh.setup("far (cm)", KINECT_MAX_DIST, KINECT_MAX_DIST, KINECT_MIN_DIST));
    kinectAngle.addListener(&Global::kinect, &Kinect::onAngleChanged);
    kinectNearThresh.addListener(&Global::kinect, &Kinect::onNearThreshChanged);
    kinectFarThresh.addListener(&Global::kinect, &Kinect::onFarThreshChanged);
    kinectGUI.setSize(600, kinectGUI.getHeight());
    kinectGUI.setWidthElements(600);
}

void GUI::draw()
{
    if (!bHide)
        kinectGUI.draw();
}