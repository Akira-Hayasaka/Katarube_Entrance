//
//  Content.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Content.hpp"

void Content::setup()
{
    fullScreen.allocate(APP_W, APP_H);
    
    ofLoadImage(bgLeft, "imgs/common/bg_left.png");
    ofLoadImage(bgMaskLeft, "imgs/common/bgMask_left.png");
    ofLoadImage(bgRight, "imgs/common/bg_right.png");
    ofLoadImage(bgMaskRight, "imgs/common/bgMask_right.png");
    
    mouth.setup("imgs/seq/mouth/1", "imgs/seqBlendTex");
    mouth.play();
}

void Content::update()
{
    mouth.update();
}

void Content::genFullScreenContent()
{
    fullScreen.begin();
    ofClear(0);
    
    bgLeft.draw(0, 0);
    mouth.draw(bgMaskLeft, bgLeft);
    
    bgRight.draw(PROJ_W, 0);
    
    fullScreen.end();
}

void Content::drawLeft()
{
    fullScreen.getTexture().drawSubsection(0, 0, PROJ_W, PROJ_H, 0, 0);
}

void Content::drawRight()
{
    fullScreen.getTexture().drawSubsection(PROJ_W, 0, PROJ_W, PROJ_H, PROJ_W, 0);    
}
