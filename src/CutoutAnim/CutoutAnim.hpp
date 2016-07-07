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
#include "Globals.hpp"
#include "Util.h"
#include "Knife.hpp"
#include "Portrait.hpp"

class CutoutAnim
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return cutoutFullScreen.getTexture(); }
    
private:
    
    void onTickEvent();
    
    bool bNeedThickUpdate;
    
    ofFbo cutoutFullScreen;
    ofShader blendCutout;
    
    Knife knife;
    Portrait portrait;
};

#endif /* CutoutAnim_hpp */
