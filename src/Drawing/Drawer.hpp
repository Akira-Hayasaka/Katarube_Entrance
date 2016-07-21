//
//  Drawer.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef Drawer_hpp
#define Drawer_hpp

#include "ofMain.h"
#include "Globals.hpp"
#include "Util.h"
#include "Painting.hpp"
#include "Puppet.hpp"

class Drawer
{
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    void onBeginLogoEvent();
    void onBeginInfoEvent();
    void onFadeOutLogoEvent();
    void onFadeOutInfoEvent();
    void onPutPuppetEvent();
    
    Painting logo;
    vector<Painting> nowExibits;
    
    vector<Puppet> puppetOriginals;
    deque<Puppet> puppetWorkingCopies;
};

#endif /* Drawer_hpp */
