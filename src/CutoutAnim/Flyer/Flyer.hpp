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
    
    void onFlyerFishLikeEvent();
    void onFlyerWavyEvent();
    void onFlyerStraightThingEvent();
    
    void clearScrn();
    void onTickEvent();
    
    ofFbo scrn;
    
    FishLike fishLike;
    Wavy wavy;
    StraightThing strtThing;
    deque<FishLike> fishLikes;
    deque<Wavy> wavys;
    deque<StraightThing> strtThings;
};
#endif /* Flyer_hpp */
