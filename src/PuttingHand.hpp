//
//  PuttingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef PuttingHand_hpp
#define PuttingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"

class PuttingHand : public BodyBase
{
public:
    
    void setup(string seqDirPath);
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onPutEvent();
    void onEndEmerge(float* arg);
    void onEndRetire(float* arg);    
    
    float startDoingTime;
    float doingDur;
};

#endif /* PuttingHand_hpp */
