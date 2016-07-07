//
//  CutoutAnim.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/7/16.
//
//

#include "CutoutAnim.hpp"

void CutoutAnim::setup()
{
    cutoutFullScreen.allocate(APP_W, APP_H);
    blendCutout.load("shaders/common/simpleVert.vert", "shaders/scene/blendCutout.frag");
    
    knife.setup();
    portrait.setup();
    
    ofAddListener(Global::tickEvent, this, &CutoutAnim::onTickEvent);
    
    bNeedThickUpdate = false;
}

void CutoutAnim::update()
{
    knife.update();
    portrait.update();
    
    if (bNeedThickUpdate)
    {
        cutoutFullScreen.begin();
        ofClear(0);
        blendCutout.begin();
        blendCutout.setUniformTexture("knife", knife.getTexture(), 0);
        blendCutout.setUniformTexture("portrait", portrait.getTexture(), 1);
        drawPlane(cutoutFullScreen.getWidth(), cutoutFullScreen.getHeight());
        blendCutout.end();
        cutoutFullScreen.end();
        bNeedThickUpdate = false;
    }
}

void CutoutAnim::onTickEvent()
{
    bNeedThickUpdate = true;
}