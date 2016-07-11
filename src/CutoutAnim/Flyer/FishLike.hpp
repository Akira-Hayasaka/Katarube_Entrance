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
    
    void onEndMove(float* arg) { bMoving = false; }
    
    bool leftToRight;
};

#endif /* FishLike_hpp */
