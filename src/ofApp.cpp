#include "ofApp.h"

void ofApp::setup()
{
	disableEdgeSwipeGesture();

	ofToggleFullscreen();
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::gray);
    ofSetFrameRate(60);
    
    Global::ELAPSED_TIME = ofGetElapsedTimef();
    Global::lastTickTime = Global::ELAPSED_TIME;
    Global::oneFrameDur = 1.0 / CUTOFF_FPS;
    Global::appState = NONE;
	Global::chromaKey.load("shaders/common/simpleVert.vert", "shaders/color/chromaKey.frag");
    Global::kinect.setup();
    Global::projMats.resize(NUM_PROJ);
    Global::box2d.init();
    Global::box2d.setGravity(-1.0, 0.0);
    Global::box2d.createBounds(ofRectangle(0, 0, APP_W, APP_H)); // need to be mask shape
    Global::box2d.setFPS(60);
    Global::scrnQuad.getVertices().resize(4);
    Global::scrnQuad.getTexCoords().resize(4);
    Global::scrnQuad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    Tweenzor::init();
    
    content.setup();
    
    gui.setup();
    gui.hide();
    
    ofNotifyEvent(Global::tickEvent);
    
    // debug
    bDrawTiny = true;
}

void ofApp::update()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    Global::ELAPSED_TIME = ofGetElapsedTimef();
    if (Global::ELAPSED_TIME - Global::lastTickTime > Global::oneFrameDur)
    {
        ofNotifyEvent(Global::tickEvent);
        Global::lastTickTime = Global::ELAPSED_TIME;
    }
    Global::kinect.update();
    content.update();
    gui.update();
    
    content.genFullScreenContent();    
}

void ofApp::draw()
{
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
    if (key == 'e')
    {
        ofNotifyEvent(Global::eatEvent);
    }
    if (key == 'd')
    {
        if (Global::appState == NONE)
        {
            Global::appState = DRAWING;
            ofNotifyEvent(Global::drawEvent);
        }
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
