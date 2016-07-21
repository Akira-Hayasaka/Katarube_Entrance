#include "ofApp.h"

void ofApp::setup()
{
	disableEdgeSwipeGesture();

    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofBackground(ofColor::black);
    ofSetFrameRate(60);
    
    Globals::ELAPSED_TIME = ofGetElapsedTimef();
    Globals::oneFrameDur = 1.0 / CUTOFF_FPS;
    Globals::lastTickTime = Globals::ELAPSED_TIME;
    Globals::curTickFrame = 0;
	Globals::chromaKey.load("shaders/common/simpleVert.vert", "shaders/color/chromaKey.frag");
    Globals::whitize.load("shaders/common/simpleVert.vert", "shaders/color/whitize.frag");
    Globals::strokeMask.load("shaders/common/simpleVert.vert", "shaders/scene/stroke.frag");
    Globals::kinect.setup();
    Globals::projMats.resize(NUM_PROJ);
    Globals::box2d.init();
    Globals::box2d.setGravity(0.0, 1.0);
//    Globals::box2d.createBounds(ofRectangle(0, 0, APP_W, APP_H)); // need to be mask shape
    Globals::box2d.setFPS(30);
    Globals::scrnQuad.getVertices().resize(4);
    Globals::scrnQuad.getTexCoords().resize(4);
    Globals::scrnQuad.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    ofDirectory blendDir("imgs/seqBlendTex");
    blendDir.listDir();
    for (int i = 0; i < blendDir.size(); i++)
    {
        ofFile f = blendDir.getFile(i);
        if (isImgFile(f.getExtension()))
        {
            ofTexture t;
            Globals::bodyBlendTexs.push_back(t);
            ofLoadImage(Globals::bodyBlendTexs.back(), f.getAbsolutePath());
        }
    }
    blendDir.close();
    Globals::petip.load("imgs/pentip/pentip.png");
    Globals::petip.resize(32, 32);
    
    Tweenzor::init();
    
    tContourFinder.setup();
    workflow.setup();
    content.setup();
    
    gui.setup(Globals::inkUniforms);
    gui.hide();
    
    ofNotifyEvent(Globals::tickEvent);
    
    workflow.goCutout();
    Globals::curAppState = workflow.getCurStateStr();
    
    // debug
    bDrawTiny = true;
}

void ofApp::update()
{
    Tweenzor::update(ofGetElapsedTimeMillis());
    Globals::ELAPSED_TIME = ofGetElapsedTimef();
    Globals::box2d.update();
    Globals::curAppState = workflow.getCurStateStr();
    if (Globals::ELAPSED_TIME - Globals::lastTickTime > Globals::oneFrameDur)
    {
        ofNotifyEvent(Globals::tickEvent);
        Globals::lastTickTime = Globals::ELAPSED_TIME;
        Globals::curTickFrame++;
    }
    Globals::kinect.update();
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
        ofMultMatrix(Globals::projMats.at(0));
        content.drawLeft();
        ofPopMatrix();
        
        ofPushMatrix();
        ofMultMatrix(Globals::projMats.at(1));
        content.drawRight();
        ofPopMatrix();
    }
    
    if (gui.isVisible())
        content.drawB2DEdge();
    gui.draw();
    
    ofPushStyle();
    for (int i = 0; i < circles.size(); i++)
    {
        ofFill();
        ofSetHexColor(0x90d4e3);
        circles[i].get()->draw();
    }
    ofPopStyle();

    ofDrawBitmapStringHighlight("State: " + workflow.getCurStateStr(), 10, ofGetHeight()-60);
    ofDrawBitmapStringHighlight("Tw: " + ofToString(Tweenzor::getSize()), 10, ofGetHeight()-40);
    ofDrawBitmapStringHighlight("fps: " + ofToString(ofGetFrameRate(), 2), 10, ofGetHeight()-20);
}

void ofApp::keyPressed(int key)
{
    if (key == '1')
        workflow.goCutout();
    if (key == '2')
        workflow.goLogo();
    if (key == '3')
        workflow.goInfo();
    if (key == '4')
        workflow.goFlushInk();
    if (key == '5')
        workflow.goInteractive();
    
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
        ofNotifyEvent(Globals::eatEvent);
    }
    if (key == 'd')
    {
        ofPoint dest(ofRandom(500, APP_W-500), ofRandom(300, APP_H-300));
        ofNotifyEvent(Globals::drawEvent, dest);
    }
    if (key == 'f')
    {
        ofNotifyEvent(Globals::fetchEvent);
    }
    if (key == 'p')
    {
        ofPoint dest(ofRandom(500, APP_W-500), ofRandom(300, APP_H-300));
        ofNotifyEvent(Globals::putEvent, dest);
    }
    if (key == 's')
    {
        ofNotifyEvent(Globals::swipeEvent);
    }
    if (key == 'a')
    {
//        vector<ofEvent<void> > evnts;
//        evnts.push_back(Globals::portraitOnePlaceEvent);
//        evnts.push_back(Globals::portraitHorizEvent);
//        evnts.push_back(Globals::portraitVertEvent);
//        evnts.push_back(Globals::flyerFishLikeEvent);
//        evnts.push_back(Globals::flyerWavyEvent);
//        evnts.push_back(Globals::flyerStraightThingEvent);
//        ofRandomize(evnts);
//        ofNotifyEvent(evnts.front());
        
        ofNotifyEvent(Globals::portraitOnePlaceEvent);
        ofNotifyEvent(Globals::portraitHorizEvent);
        ofNotifyEvent(Globals::portraitVertEvent);
        ofNotifyEvent(Globals::flyerFishLikeEvent);
        ofNotifyEvent(Globals::flyerWavyEvent);
        ofNotifyEvent(Globals::flyerStraightThingEvent);
        ofNotifyEvent(Globals::kyoEvent);
        ofNotifyEvent(Globals::knifeCircleEvent);
        ofNotifyEvent(Globals::inkEvent);
    }
    if (key == 'c')
    {
        float r = ofRandom(4, 20);		// a random radius 4px - 20px
        circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));
        circles.back().get()->setPhysics(3.0, 0.53, 0.1);
        circles.back().get()->setup(Globals::box2d.getWorld(), mouseX, mouseY, r);
    }
    if (key == 'm')
    {
        for (int i = 0; i < 10; i++)
            ofNotifyEvent(Globals::inkEvent);
    }
    if (key == 'z')
    {
        ofNotifyEvent(Globals::putPuppetEvent);
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
