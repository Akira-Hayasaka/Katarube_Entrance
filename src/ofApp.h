#pragma once

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"
#include "WorkFlow.hpp"
#include "Content.hpp"
#include "ThreadedContourFinder.hpp"
#include "GUI.hpp"

class ofApp : public ofBaseApp
{
public:
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    
    WorkFlow workflow;    
    Content content;
    GUI gui;
    ThreadedContourFinder tContourFinder;
    ofPtr<ofxBox2d> box2d;
    
    // debug
    bool bDrawTiny;
    vector<shared_ptr<ofxBox2dCircle> > circles;
};
