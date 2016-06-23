#include "ofApp.h"

void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    
    Global::kinect.setup();
    Global::projMats.resize(NUM_PROJ);
    
    gui.setup();
    
    // debug
    ofLoadImage(fullScrn, "imgs/debug/fullScreen/gLA9Lde.jpg");
    projFbo1.allocate(PROJ_W, PROJ_H);
	projFbo2.allocate(PROJ_W, PROJ_H);
    kinectFbo.allocate(KINECT_W, KINECT_H);
	projFbo1.begin();
    ofClear(0);
    ofPushStyle();
    ofSetColor(ofColor::blue, 100);
    ofDrawRectangle(0, 0, projFbo1.getWidth(), projFbo1.getHeight());
    ofPopStyle();
	projFbo1.end();
	projFbo2.begin();
	ofClear(0);
	ofPushStyle();
	ofSetColor(ofColor::cyan, 100);
	ofDrawRectangle(0, 0, projFbo2.getWidth(), projFbo2.getHeight());
	ofPopStyle();
	projFbo2.end();
    kinectFbo.begin();
    ofClear(0);
    ofSetColor(ofColor::pink, 100);
	ofDrawRectangle(0, 0, kinectFbo.getWidth(), kinectFbo.getHeight());
    kinectFbo.end();
}

void ofApp::update()
{
    Global::kinect.update();
    gui.update();
    
    
    contours.clear();
    contourPaths.clear();
    
    kinectFbo.begin();
    ofClear(0);
    ofSetColor(ofColor::pink);
    
    for (auto c : contours)
        c.draw();
    kinectFbo.end();
    
    for (auto& c : contours)
    {
        int idx = 0;
        ofPath path;
        for (auto& p : c.getVertices())
        {
            p = p * Global::kinectMat;
            
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
    
    ofPushMatrix();
    ofMultMatrix(Global::kinectMat);
    kinectFbo.draw(0, 0);
    ofPopMatrix();
    
    ofPushStyle();
    ofFill();
    ofSetColor(ofColor::yellow, 150);
    for (auto c : contourPaths)
        c.draw();
    ofPopStyle();
    
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
