//
//  BodyBase.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/18/16.
//
//

#ifndef BodyBase_hpp
#define BodyBase_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"

class BodyBase
{
public:
    
    void setup(string seqDirPath);
    void update();
    void draw();
    
protected:
    
    void genTweakTex();
    virtual void onTickEvent() = 0;
    
    enum STATE
    {
        NONE,
        EMERGE,
        DOING,
        RETIRE
    };
    STATE state;
    
    ofPoint posOrig;
    ofPoint posDest;
    ofPoint curPos;
    
    int curFrame;
    int blendIdx;
    
    vector<ofFbo> seq;
    ofShader seqTweak;
    ofFbo tweaker;
};

#endif /* BodyBase_hpp */
