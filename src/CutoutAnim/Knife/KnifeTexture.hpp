//
//  KnifeTexture.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/13/16.
//
//

#ifndef KnifeTexture_hpp
#define KnifeTexture_hpp

#include "ofMain.h"
#include "ofxTweenzor.h"

class KnifeTexture : public ofTexture, ofNode
{
public:
    
    void setup(int idx);
    void update();
    void draw() { ofNode::draw(); }
    virtual void customDraw();
    void goCircle(ofPolyline motionLine);
    void goLine(ofPolyline motionLine);
    
private:
    
    int idx;
    ofPolyline motionLine;
    float ang;
};

#endif /* KnifeTexture_hpp */
