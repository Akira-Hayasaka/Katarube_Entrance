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
    void goLogo();
    void goInfo();
    void goFlushInk();
    void goInteractive();
    
    string getCurStateStr();
    
private:
    
    void checkWorkFlow();    
    void proceedIfPossible();
    
    enum APP_STATE
    {
        CUTOUT,
        LOGO,
        INFO,
        FLUSHINK,
        INTERACTION
    };
    APP_STATE appState;
    
    vector<EventTimer> cutoutEvents;
    
    float cutoutDur;
    float cutoutBeginTime;
    
    float logoDur;
    float logoBeginTime;
    bool bFadeOutLogo;
    
    float infoDur;
    float infoBeginTime;
    bool bFadeOutInfo;
    
    float flushInkDur;
    float flushInkBeginTime;
    bool bFadeOutInk;
    
    float interactionBeginTime;
};

#endif /* WorkFlow_hpp */
