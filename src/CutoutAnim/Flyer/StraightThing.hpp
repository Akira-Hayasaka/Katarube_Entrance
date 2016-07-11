//
//  StraightThing.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef StraightThing_hpp
#define StraightThing_hpp

#include "FlyerBase.hpp"

class StraightThing : public FlyerBase
{
public:
    
    virtual void go();
    virtual void customDraw();
    
private:
    
    bool bLeftToRight;
    void onEndMove(float* arg) { bMoving = false; }
};

#endif /* StraightThing_hpp */
