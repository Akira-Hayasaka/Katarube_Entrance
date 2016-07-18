#include "ofApp.h"

void ofApp::setup()
{
	disableEdgeSwipeGesture();

    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    ofSetFrameRate(60);
    
    Global::ELAPSED_TIME = ofGetElapsedTimef();
    Global::oneFrameDur = 1.0 / CUTOFF_FPS;
    Global::lastTickTime = Global::ELAPSED_TIME;
    Global::curTickFrame = 0;
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
    ofDirectory blendDir("imgs/seqBlendTex");
    blendDir.listDir();
    for (int i = 0; i < blendDir.size(); i++)
    {
        ofFile f = blendDir.getFile(i);
        if (isImgFile(f.getExtension()))
        {
            ofTexture t;
            Global::bodyBlendTexs.push_back(t);
            ofLoadImage(Global::bodyBlendTexs.back(), f.getAbsolutePath());
        }
    }
    blendDir.close();
    
    Tweenzor::init();
    
    workflow.setup();
    content.setup();
    
    gui.setup(Global::inkUniforms);
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
        Global::curTickFrame++;
    }
    Global::kinect.update();
    workflow.update();
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
    
    if (gui.isVisible())
        content.drawB2DEdge();
    gui.draw();
    
    ofDrawBitmapStringHighlight("Tw: " + ofToString(Tweenzor::getSize()), 10, ofGetHeight()-40);
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight()-20);
}

void ofApp::keyPressed(int key)
{
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
        ofNotifyEvent(Global::drawEvent);
    }
    if (key == 'f')
    {
        ofNotifyEvent(Global::fetchEvent);
    }
    if (key == 'p')
    {
        ofNotifyEvent(Global::putEvent);
    }
    if (key == 's')
    {
        content.saveScreen();
    }
    if (key == 'e')
    {
//        vector<ofEvent<void> > evnts;
//        evnts.push_back(Global::portraitOnePlaceEvent);
//        evnts.push_back(Global::portraitHorizEvent);
//        evnts.push_back(Global::portraitVertEvent);
//        evnts.push_back(Global::flyerFishLikeEvent);
//        evnts.push_back(Global::flyerWavyEvent);
//        evnts.push_back(Global::flyerStraightThingEvent);
//        ofRandomize(evnts);
//        ofNotifyEvent(evnts.front());
        
        ofNotifyEvent(Global::portraitOnePlaceEvent);
        ofNotifyEvent(Global::portraitHorizEvent);
        ofNotifyEvent(Global::portraitVertEvent);
        ofNotifyEvent(Global::flyerFishLikeEvent);
        ofNotifyEvent(Global::flyerWavyEvent);
        ofNotifyEvent(Global::flyerStraightThingEvent);
        ofNotifyEvent(Global::kyoEvent);
        ofNotifyEvent(Global::knifeCircleEvent);
        ofNotifyEvent(Global::inkEvent);
    }
    if (key == 'c')
    {
        ofNotifyEvent(Global::clearInkEvent);
    }
    if (key == 'm')
    {
        for (int i = 0; i < 10; i++)
            ofNotifyEvent(Global::inkEvent);
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
