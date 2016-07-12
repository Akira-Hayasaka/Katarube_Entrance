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

class Knife
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void onTickEvent();
    
    bool bNeedTickUpdate;
    
    ofFbo scrn;
    
    vector<ofTexture> texs;
};

#endif /* Knife_hpp */
