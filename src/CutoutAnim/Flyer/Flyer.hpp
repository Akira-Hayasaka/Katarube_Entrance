//
//  Flyer.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef Flyer_hpp
#define Flyer_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "FishLike.hpp"
#include "Wavy.hpp"
#include "StraightThing.hpp"

class Flyer
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void onFlyerFishLikeEvent() { fishLike.go(); }
    void onFlyerWavyEvent() { wavy.go(); }
    void onFlyerStraightThingEvent() { strtThing.go(); }
    
    void clearScrn();
    void onTickEvent();
    
    ofFbo scrn;
    
    FishLike fishLike;
    Wavy wavy;
    StraightThing strtThing;
};
#endif /* Flyer_hpp */
