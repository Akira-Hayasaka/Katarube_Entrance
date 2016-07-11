//
//  Wavy.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef Wavy_hpp
#define Wavy_hpp

#include "FlyerBase.hpp"

class Wavy : public FlyerBase
{
public:
    
    virtual void go();
    virtual void customDraw();   
    
private:
    
    void onEndMove(float* arg) { bMoving = false; }
};

#endif /* Wavy_hpp */
