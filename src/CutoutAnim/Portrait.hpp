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
    
    // one place
    ofPoint onePlacePos;
    long lastOneFrameTick;
    int onPlaceFrameDur;
    
    // horiz
    
};

#endif /* Portrait_hpp */
