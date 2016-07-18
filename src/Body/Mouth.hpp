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
#include "BodyBase.hpp"

class Mouth : public BodyBase
{
public:
    
    void setup(string seqDirPath);
    
protected:
    
    virtual void onTickEvent();
    
private:
    
    void onEatEvent();
    void onEndEmerge(float* arg);
};

#endif /* Mouth_hpp */
