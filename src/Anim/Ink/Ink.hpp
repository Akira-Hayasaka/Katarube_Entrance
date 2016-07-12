//
//  Ink.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/11/16.
//
//

#ifndef Ink_hpp
#define Ink_hpp

#include "ofMain.h"
#include "ofxInkSim.h"
#include "Constants.h"
#include "Globals.hpp"

class Ink
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void clearScrn();
    void onInkEvent();
    void onClearInkEvent();
    
    ofFbo scrn;
    
    ofxInkSim inkSim;
    float canvasRatio, canvasW, canvasH;
    vector<ofTexture> texs;
};

#endif /* Ink_hpp */
