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
    
    Painting logo;
    vector<Painting> nowExibits;
    
    vector<Puppet> puppets;
};

#endif /* Drawer_hpp */
