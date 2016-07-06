//
//  Content.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#ifndef Content_hpp
#define Content_hpp

#include "ofMain.h"
#include "Mouth.hpp"

class Content
{
public:
    
    void setup();
    void update();
    void genFullScreenContent();
    void drawLeft();
    void drawRight();
    ofTexture& getFullScreenTexture() { return fullScreen.getTexture(); }
    
private:
    
    ofFbo fullScreen;
    
    ofTexture bgRight;
    ofTexture bgMaskRight;
    ofTexture bgLeft;
    ofTexture bgMaskLeft;
    
    Mouth mouth;
};

#endif /* Content_hpp */
