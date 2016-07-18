//
//  DrawingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef DrawingHand_hpp
#define DrawingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"

class DrawingHand : public BodyBase
{
public:
    
    void setup(string seqDirPath);
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onDrawEvent();
    void onEndEmerge(float* arg);
    void onEndRetire(float* arg);
    
    float startDoingTime;
    float doingDur;
};

#endif /* DrawingHand_hpp */
