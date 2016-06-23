#include "ofApp.h"

void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    Global::kinect.setup();
    gui.setup();
    
    // debug
    ofLoadImage(fullScrn, "imgs/debug/fullScreen/gLA9Lde.jpg");
    testFbo.allocate(PROJ_W, PROJ_H);
    testFbo.begin();
    ofClear(0);
    ofPushStyle();
    ofSetColor(ofColor::red);
    ofDrawRectangle(0, 0, testFbo.getWidth(), testFbo.getHeight());
    ofPopStyle();
    testFbo.end();
}

void ofApp::update()
{
    Global::kinect.update();
    gui.update();
}

void ofApp::draw()
{
    fullScrn.draw(0, 0);
    
    ofMatrix4x4 mat = Global::testMat;
    
    ofPushMatrix();
    ofMultMatrix(mat);
    testFbo.draw(0, 0);
    ofPopMatrix();
    
    gui.draw();
    
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight()-20);
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
