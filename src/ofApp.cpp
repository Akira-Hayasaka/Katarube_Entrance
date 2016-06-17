#include "ofApp.h"

void ofApp::setup()
{
    Global::kinect.setup();
    gui.setup();
    
    depthTex.allocate(KINECT_W, KINECT_H, GL_RGB);
}

void ofApp::update()
{
    Global::kinect.update();
}

void ofApp::draw()
{
    if (Global::kinect.isInited())
    {
        Global::kinect.getDepthTexture().draw(0, 0, KINECT_W/2, KINECT_H/2);
        Global::kinect.getThreshedTexture().draw(KINECT_W/2, 0, KINECT_W/2, KINECT_H/2);        
    }
    
    gui.draw();
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
