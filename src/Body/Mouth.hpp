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
#include "Globals.hpp"

class Mouth
{
public:
    
    void setup(string seqDirPath, string blendDirPath);
    void play();
    void stop() { bPlay = false; };
    void update();
    void draw(const ofTexture& bgMask, const ofTexture& bg);
    
private:
    
    const int FPS = 12;
    
    bool bPlay;
    float lastTickTime;
    float oneFrameDur;
    int curFrame;
    vector<ofFbo> seq;
    int blendIdx;
    vector<ofTexture> blendTexs;
    ofFbo tweaker;
    ofShader seqTweak;    
};

#endif /* Mouth_hpp */
