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
#include "Constants.h"
#include "Globals.hpp"

class Mouth
{
public:
    
    void setup(string seqDirPath, string blendDirPath);
    void play();
    void stop() { bPlay = false; };
    void draw(const ofTexture& bgMask, const ofTexture& bg);
    
private:
    
    void tick();    
    
    bool bPlay;
    int curFrame;
    vector<ofFbo> seq;
    int blendIdx;
    vector<ofTexture> blendTexs;
    ofShader seqTweak;    
};

#endif /* Mouth_hpp */
