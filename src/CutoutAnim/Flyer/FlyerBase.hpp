//
//  FlyerBase.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef FlyerBase_hpp
#define FlyerBase_hpp

#include "ofMain.h"
#include "Globals.hpp"

class FlyerBase : public ofNode
{
public:
    
    void setup(string seqDir);
    void update();
    virtual void customDraw();
    
    virtual void go() = 0;
    
protected:
    
    void onTickEvent();
    
    int lastTickFrame;
    
    int texIdx;
    vector<ofTexture> texs;
    
};

#endif /* FlyerBase_hpp */
