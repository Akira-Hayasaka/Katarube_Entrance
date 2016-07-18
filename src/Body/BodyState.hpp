//
//  BodyState.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/18/16.
//
//

#ifndef BodyState_hpp
#define BodyState_hpp

#include "ofMain.h"
#include "Globals.hpp"

class BodyState
{
public:
    
    BodyState()
    {
        curFrame = 0;
        blendIdx = ofRandom(Global::bodyBlendTexs.size()-1);
        state = NONE;
    }
    
    enum STATE
    {
        NONE,
        EMERGE,
        DOING,
        RETIRE,
        DONE
    };
    STATE state;
    
    ofPoint posOrig;
    ofPoint posDest;
    ofPoint curPos;
    
    int curFrame;
    int blendIdx;
};

#endif /* BodyState_hpp */
