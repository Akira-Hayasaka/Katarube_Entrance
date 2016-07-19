//
//  Drawing.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef Drawing_hpp
#define Drawing_hpp

#include "ofMain.h"
#include "Globals.hpp"

class Drawing
{
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    void onBeginLogoInfoEvent();
};

#endif /* Drawing_hpp */
