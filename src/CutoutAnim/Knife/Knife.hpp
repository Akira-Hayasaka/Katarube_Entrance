//
//  Knife.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#ifndef Knife_hpp
#define Knife_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Knives.hpp"

class Knife
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void clearScrn();
    void onTickEvent();
    void onKnifeCircleEvent();
    
    ofFbo scrn;
    
    vector<Knives> knives;
    deque<Knives> worksets;
};

#endif /* Knife_hpp */
