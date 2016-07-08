//
//  Portrait.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#ifndef Portrait_hpp
#define Portrait_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"
#include "ofxTweenzor.h"

static bool compareHeight(const ofTexture& p1, const ofTexture& p2)
{
    return p1.getHeight() < p2.getHeight();
}

class Portrait
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void clearScrn();
    void onTickEvent();
    void onPortraitOnePlaceEvent();
    void onPortraitHorizEvent();
    void beginShake(ofPoint pos, float scaleF = 1.0);
    void endShake();
    
    enum PATTERN
    {
        NONE,
        ONEPLACE,
        HORIZ,
        VERT,
        FLIP,
        TILE
    };
    PATTERN pattern;
    
    ofFbo scrn;
    vector<ofTexture> texs;
    int texIdx;
    
    long beginTickFrame;
    long lastOneFrameTick;    
    
    // one place
    ofPoint onePlacePos;
    int onPlaceFrameDur;
    
    // horiz
    vector<ofPoint> horizFroms;
    vector<ofPoint> horizTos;
    vector<ofPoint> curHorizPos;
    int horizRot;
    ofPoint horizRotCen;
    int horizStartIdx;
    int horixStartInterval;
    int horizFinishCnt;
    void onEndOneHorizMovement(float* arg);
    
    // vert
    vector<ofPoint> vertFroms;
    vector<ofPoint> vertTos;
    vector<ofPoint> curVertPoss;
};

#endif /* Portrait_hpp */
