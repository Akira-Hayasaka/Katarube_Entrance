//
//  KyoTexture.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/12/16.
//
//

#ifndef KyoTexture_hpp
#define KyoTexture_hpp

#include "ofMain.h"
#include "ofxTweenzor.h"
#include "Constants.h"
#include "Globals.hpp"
#include "Util.h"

class KyoTexture : public ofTexture
{
public:
    
    KyoTexture() { bRunning = false; }
    void go();
    void draw();
    bool isRunning() { return bRunning; }
    
private:
    
    void onEndIn(float* arg);
    void onEndOut(float* arg);
    
    bool bRunning;
    
    ofPoint pos;
    float curScale;
    float destScale;
    float curAlpha;
    float destAlpha;
    float ang;
};

#endif /* KyoTexture_hpp */
