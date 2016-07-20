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
        }
    }
    exbitDir.close();
    
    ofAddListener(Global::beginLogoEvent, this, &Drawer::onBeginLogoEvent);
}

void Drawer::update()
{
    logo.update();
}

void Drawer::draw()
{
    logo.draw();
//    logo.drawOutline();
}

void Drawer::onBeginLogoEvent()
{
    ofPoint leftDest(ofRandom(500, APP_W-500), ofRandom(300, APP_H-300));
    logo.beginDrawWContour();
}