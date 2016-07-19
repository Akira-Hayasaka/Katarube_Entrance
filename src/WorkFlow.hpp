//
//  WorkFlow.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/15/16.
//
//

#ifndef WorkFlow_hpp
#define WorkFlow_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Globals.hpp"
#include "EventTimer.hpp"

class WorkFlow
{
public:
    
    void setup();
    void update();
    
    void goCutout();
    void goLogoInfo();
    void goFlushScreen();
    void goInteractive();
    
    string getCurStateStr();
    
private:
    
    void proceed();
    
    enum APP_STATE
    {
        CUTOUT,
        LOGOINFO,
        FLUSHSCREEN,
        INTERACTION
    };
    APP_STATE appState;
    
    vector<EventTimer> cutoutEvents;
    
    float cutoutDur;
    float logoInfoDur;
    float flushScreenDur;
    float cutoutBeginTime;
    float logoInfoBeginTime;
    float flushSceenBeginTime;
};

#endif /* WorkFlow_hpp */
