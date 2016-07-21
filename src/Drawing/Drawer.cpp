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
    
    ofDirectory puppetDir("imgs/puppets");
    puppetDir.listDir();
    for (int i = 0; i < puppetDir.size(); i++)
    {
        ofFile f = puppetDir.getFile(i);
        if (isImgFile(f.getExtension()))
        {
            Puppet p;
            puppetOriginals.push_back(p);
            puppetOriginals.back().setup(f.getAbsolutePath(), true, true);
        }
    }
    puppetDir.close();
    
    ofAddListener(Globals::beginLogoEvent, this, &Drawer::onBeginLogoEvent);
    ofAddListener(Globals::beginInfoEvent, this, &Drawer::onBeginInfoEvent);
    ofAddListener(Globals::fadeOutLogoEvent, this, &Drawer::onFadeOutLogoEvent);
    ofAddListener(Globals::fadeOutInfoEvent, this, &Drawer::onFadeOutInfoEvent);
    ofAddListener(Globals::putPuppetEvent, this, &Drawer::onPutPuppetEvent);
}

void Drawer::update()
{
    logo.update();
    
    for (auto& ne : nowExibits)
        ne.update();
    
    for (auto& pwc : puppetWorkingCopies)
        pwc.update();
}

void Drawer::draw()
{
    logo.draw();
    
    for (auto ne : nowExibits)
        ne.draw();
    
    for (auto pwc : puppetWorkingCopies)
        pwc.draw();
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

void Drawer::onPutPuppetEvent()
{
    puppetWorkingCopies.push_back(puppetOriginals.at(ofRandom(puppetOriginals.size())));
    puppetWorkingCopies.back().setPosition(ofPoint(ofRandom(600, APP_W - 600),
                                                   ofRandom(300, APP_H - 300)));
    puppetWorkingCopies.back().beginDraw();
}