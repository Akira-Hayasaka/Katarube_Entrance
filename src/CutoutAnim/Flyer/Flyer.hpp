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

class Flyer
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void clearScrn();
    void onTickEvent();
    
    ofFbo scrn;
};
#endif /* Flyer_hpp */
