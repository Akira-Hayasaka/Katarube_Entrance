//
//  Knives.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/13/16.
//
//

#ifndef Knives_hpp
#define Knives_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Util.h"
#include "KnifeTexture.hpp"

class Knives
{
public:
    
    void setup(string dirPath);
    void update();
    void draw();
    void goCircle();
    void goLine();
    
private:
    
    bool bRunning;
    
    float rot;
    ofPoint pos;
    vector<KnifeTexture> texs;
};

#endif /* Knives_hpp */
