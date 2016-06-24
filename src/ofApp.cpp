#include "ofApp.h"

void ofApp::setup()
{
	disableEdgeSwipeGesture();

	ofToggleFullscreen();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    
    Global::kinect.setup();
    Global::projMats.resize(NUM_PROJ);
    
    gui.setup();
    
    // debug
    ofLoadImage(fullScrn, "imgs/tweak/fullScreen/gLA9Lde.jpg");
    projFbo1.allocate(PROJ_W, PROJ_H);
	projFbo2.allocate(PROJ_W, PROJ_H);
	projFbo1.begin();
    ofClear(0);
    ofPushStyle();
    ofSetColor(ofColor::blue, 160);
    ofDrawRectangle(0, 0, projFbo1.getWidth(), projFbo1.getHeight());
    ofPopStyle();
	projFbo1.end();
	projFbo2.begin();
	ofClear(0);
	ofPushStyle();
	ofSetColor(ofColor::cyan, 160);
	ofDrawRectangle(0, 0, projFbo2.getWidth(), projFbo2.getHeight());
	ofPopStyle();
	projFbo2.end();
}

void ofApp::update()
{
    Global::kinect.update();
    gui.update();
}

void ofApp::draw()
{
    fullScrn.draw(0, 0);
    
    ofPushMatrix();
    ofMultMatrix(Global::projMats.at(0));
	projFbo1.draw(0, 0);
    ofPopMatrix();

	ofPushMatrix();
	ofMultMatrix(Global::projMats.at(1));
	projFbo2.draw(0, 0);
	ofPopMatrix();
    
    gui.draw();
    
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight()-20);
}

void ofApp::keyPressed(int key)
{
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
    if (key == 'w')
    {
        gui.saveProjWarp();
        gui.saveKinectWarp();
    }
}
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
