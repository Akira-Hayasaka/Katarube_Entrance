//
//  FishLike.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/10/16.
//
//

#ifndef FishLike_hpp
#define FishLike_hpp

#include "FlyerBase.hpp"

class FishLike : public FlyerBase
{
public:
    
    virtual void go();
    virtual void customDraw();    
    
private:
    
    bool leftToRight;
    void onEndMove(float* arg) { bMoving = false; }    
};

#endif /* FishLike_hpp */
