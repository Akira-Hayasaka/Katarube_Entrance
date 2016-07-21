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
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"
#include "Knife.hpp"
#include "Portrait.hpp"
#include "Flyer.hpp"
#include "Kyo.hpp"

class CutoutAnim
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return cutoutFullScreen.getTexture(); }
    
private:
    
    void onTickEvent();
    void onFadeOut();
    void onFadeIn();
    
    ofFbo cutoutFullScreen;
    ofShader blendCutout;
    
    Knife knife;
    Portrait portrait;
    Flyer flyer;
    Kyo kyo;
    
    float alpha;
};

#endif /* CutoutAnim_hpp */
