//
//  Portraits.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#ifndef Portraits_hpp
#define Portraits_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"
#include "PortraitTexture.hpp"

static bool compareHeight(const ofTexture& p1, const ofTexture& p2)
{
    return p1.getHeight() < p2.getHeight();
}

class Portraits
{
public:
    
    void setup();
    void update();

    void onTick();
    void onPortraitOnePlace();
    void onPortraitHoriz();
    void onPortraitVert();
    
    bool isDone() { return (pattern == DONE) ? true : false; }
    
private:

    void checkDone();
    
    enum PATTERN
    {
        NONE,
        ONEPLACE,
        HORIZ,
        VERT,
        DONE
    };
    PATTERN pattern;
    
    vector<PortraitTexture> texs;
    vector<PortraitTexture*> workingTexs;
    int texIdx;
    long beginTickFrame;
    long lastOneFrameTick;
    
    // one place
    int onPlaceFrameDur;
    float onePlaceAng;
    
    // horiz
    int horizRot;
    ofPoint horizRotCen;
    
    // vert
    vector<BottomLineAndAng> bottomLineAndAngSimplified;
};

#endif /* Portraits_hpp */
