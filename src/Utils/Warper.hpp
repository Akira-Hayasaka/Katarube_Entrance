//
//  Warper.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/23/16.
//
//

#ifndef Warper_hpp
#define Warper_hpp

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "Constants.h"

class Warper : public ofxQuadWarp
{
public:
    
    void setup();
    void update();
    
    ofMatrix4x4 getMatEx() { return scaledMat; }
    
private:
    
    ofPoint dstCenter;
    ofMatrix4x4 scaledMat;
};

#endif /* Warper_hpp */
