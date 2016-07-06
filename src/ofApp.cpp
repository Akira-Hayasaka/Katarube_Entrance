#include "ofApp.h"

void ofApp::setup()
{
	disableEdgeSwipeGesture();

	ofToggleFullscreen();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    
	Global::chromaKey.load("shaders/common/simpleVert.vert", "shaders/color/chromaKey.frag");
    Global::kinect.setup();
    Global::projMats.resize(NUM_PROJ);
    
    content.setup();
    
    gui.setup();
    gui.hide();
    
    // debug
    bDrawTiny = true;
}

void ofApp::update()
{
    Global::kinect.update();
    content.update();
    gui.update();
}

void ofApp::draw()
{
    content.genFullScreenContent();
    
    if (bDrawTiny)
    {
        content.getFullScreenTexture().draw(0, 0, APP_W * 0.5, APP_H * 0.5);
    }
    else
    {
        ofPushMatrix();
        ofMultMatrix(Global::projMats.at(0));
        content.drawLeft();
        ofPopMatrix();
        
        ofPushMatrix();
        ofMultMatrix(Global::projMats.at(1));
        content.drawRight();
        ofPopMatrix();
    }
    
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
    if (key == ' ')
    {
        gui.toggleVisible();
    }
    if (key == 't')
    {
        bDrawTiny = !bDrawTiny;
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
