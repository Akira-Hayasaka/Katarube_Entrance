//
//  Drawer.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "Drawer.hpp"

void Drawer::setup()
{
    logo.setup("imgs/logo/logo.png", true);
    logo.setPosition(ofPoint(PROJ_W/2-logo.getTexture().getWidth()/2 + 100, APP_H/2));
    
    ofDirectory exbitDir("imgs/nowExibit");
    exbitDir.listDir();
    for (int i = 0; i < exbitDir.size(); i++)
    {
        ofFile f = exbitDir.getFile(i);
        if (isImgFile(f.getExtension()))
        {
            Painting ex;
            nowExibits.push_back(ex);
            nowExibits.back().setup(f.getAbsolutePath());
            nowExibits.back().setPosition(ofPoint(APP_W - PROJ_W/2 - 100,
                                                  APP_H/2));
        }
    }
    exbitDir.close();
    
    ofAddListener(Globals::beginLogoEvent, this, &Drawer::onBeginLogoEvent);
    ofAddListener(Globals::beginInfoEvent, this, &Drawer::onBeginInfoEvent);
    ofAddListener(Globals::fadeOutLogoEvent, this, &Drawer::onFadeOutLogoEvent);
    ofAddListener(Globals::fadeOutInfoEvent, this, &Drawer::onFadeOutInfoEvent);
}

void Drawer::update()
{
    logo.update();
    
    for (auto& ne : nowExibits)
        ne.update();
}

void Drawer::draw()
{
    logo.draw();
    
    for (auto ne : nowExibits)
        ne.draw();
}

void Drawer::onBeginLogoEvent()
{
    logo.beginDraw();
}

void Drawer::onBeginInfoEvent()
{
    nowExibits.at(ofRandom(nowExibits.size())).beginDraw();
}

void Drawer::onFadeOutLogoEvent()
{
    logo.fadeOut();
}

void Drawer::onFadeOutInfoEvent()
{
    for (auto& ne : nowExibits)
        ne.fadeOut();
}