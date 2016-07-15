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
#include "Globals.hpp"
#include "EventTimer.hpp"

class WorkFlow
{
public:
    
    void setup();
    void update();
    
    void goCutout();
    void goFlushScreen();
    void goInteractive();
    
private:
    
    enum APP_STATE
    {
        CUTOUT,
        FLUSHSCREEN,
        INTERACTION
    };
    APP_STATE appState;
    
    vector<EventTimer> cutoutEvents;
};

#endif /* WorkFlow_hpp */
