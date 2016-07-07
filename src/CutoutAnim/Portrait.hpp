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

class Portrait
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

#endif /* Portrait_hpp */
