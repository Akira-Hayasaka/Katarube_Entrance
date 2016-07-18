//
//  FetchingHand.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef FetchingHand_hpp
#define FetchingHand_hpp

#include "ofMain.h"
#include "BodyBase.hpp"

class FetchingHand : public BodyBase
{
public:
    
    void setup(string seqDirPath);
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onFetchEvent();
    void onEndEmerge(float* arg);
    
    float startDoingTime;
    float doingDur;
};

#endif /* FetchingHand_hpp */
