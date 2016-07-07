//
//  CutoutAnim.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#ifndef CutoutAnim_hpp
#define CutoutAnim_hpp

#include "ofMain.h"
#include "Constants.h"

class CutoutAnim
{
public:
    
    void setup();
    void update();
    ofTexture& getCutOutTex() { return cutoutFullScreen.getTexture(); }
    
private:
    
    ofFbo cutoutFullScreen;
    
    ofTexture test1;
    ofTexture test2;
};

#endif /* CutoutAnim_hpp */
