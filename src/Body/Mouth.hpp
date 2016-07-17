//
//  Mouth.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#ifndef Mouth_hpp
#define Mouth_hpp

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"

class Mouth
{
public:
    
    void setup(string seqDirPath, string blendDirPath);
    void update();
    void draw();
    
private:
    
    void genTweakTex();
    void onTickEvent();
    void onEatEvent();
    void onEndEmerge(float* arg);
    
    enum STATE
    {
        NONE,
        EMERGE,
        EATING,
        RETIRE
    };
    STATE state;

    ofPoint facePosOrig;
    ofPoint facePosDest;
    ofPoint curFacePos;    
    
    int curFrame;
    vector<ofFbo> seq;
    int blendIdx;
    vector<ofTexture> blendTexs;
    ofShader seqTweak;
    ofFbo tweaker;
};

#endif /* Mouth_hpp */
