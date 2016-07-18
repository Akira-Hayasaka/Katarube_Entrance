//
//  Body.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/18/16.
//
//

#ifndef Body_hpp
#define Body_hpp

#include "ofMain.h"
#include "BodyBase.hpp"
#include "Mouth.hpp"
#include "DrawingHand.hpp"
#include "FetchingHand.hpp"
#include "PuttingHand.hpp"
#include "SwipingHand.hpp"

class Body
{
public:
    
    void setup();
    void update();
    void draw();
    
private:
    
    void onEatEvent();
    void onDrawEvent(ofPoint& dest);
    void onFetchEvent();
    void onPutEvent();
    void onSwipeEvent();
    
    BodyBase mouthBase;
    BodyBase drawingHBase;
    BodyBase fetchingHBase;
    BodyBase puttingHBase;
    BodyBase swipingHBase;
    
    deque<Mouth> mouths;
    deque<DrawingHand> drawingHands;
    deque<FetchingHand> fetchingHands;
    deque<PuttingHand> puttingHands;
    deque<SwipingHand> swipingHands;
};

#endif /* Body_hpp */
