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
    
    vector<KnifeTexture> texs;
};

#endif /* Knives_hpp */
