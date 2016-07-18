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
#include "BodyState.hpp"

class BodyBase
{
public:
    
    void setup(string seqDirPath);
    void draw(BodyState bodyState);
    void draw(BodyState bodyState, bool bFromUpper, float ang);
    void genTweakTex(BodyState bodyState);
    
    vector<ofFbo> seq;
    ofShader seqTweak;
    ofFbo tweaker;
    ofVec2f anchor;
};

#endif /* BodyBase_hpp */
