//
//  Kyo.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/12/16.
//
//

#ifndef Kyo_hpp
#define Kyo_hpp

#include "ofMain.h"
#include "Constants.h"
#include "Globals.hpp"
#include "KyoTexture.hpp"

class Kyo
{
public:
    
    void setup();
    void update();
    ofTexture& getTexture() { return scrn.getTexture(); }
    
private:
    
    void clearScrn();
    void onTickEvent();
    void onKyoEvent();
    
    ofFbo scrn;
    
    int curIdx;
    vector<KyoTexture> texs;
};

#endif /* Kyo_hpp */
