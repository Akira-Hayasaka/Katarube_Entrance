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
#include "Portraits.hpp"

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
    
    ofFbo scrn;
    
    Portraits portrait;
    deque<Portraits> worksets;

};

#endif /* Portrait_hpp */
