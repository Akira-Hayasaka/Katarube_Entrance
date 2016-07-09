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
#include "PortraitTexture.hpp"

static bool compareHeight(const ofTexture& p1, const ofTexture& p2)
{
    return p1.getHeight() < p2.getHeight();
}

struct BottomLineAndAng
{
    ofPoint p;
    float ang;
};

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
    void onPortraitVertEvent();
    void checkDone();
    
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
    vector<PortraitTexture> texs;
    vector<PortraitTexture*> workingTexs;
    int texIdx;
    
    long beginTickFrame;
    long lastOneFrameTick;    
    
    // one place
    int onPlaceFrameDur;
    
    // horiz
    int horizRot;
    ofPoint horizRotCen;
    
    // vert
    vector<BottomLineAndAng> bottomLineAndAngs;
};

#endif /* Portrait_hpp */
