//
//  Painting.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/19/16.
//
//

#ifndef Painting_hpp
#define Painting_hpp

#include "ofMain.h"
#include "Globals.hpp"
#include "Util.h"

class Painting
{
public:
    
    enum CONTOURPHASE
    {
        NONE,
        DRAWING,
        END
    };
    
    void setup(string texPath, bool bDrawWContour = false);
    void update();
    void draw();
    void drawOutline();
    
    void setPosition(ofPoint pos) { this->pos = pos; }
    void setRot(float rot) { this->rot = rot; }
    ofTexture& getTexture() { return tex.getTexture(); }
    void beginDrawWContour();
    
private:
    
    void onGotContourEvent(DrawCommandContour& cc);
    
    bool bContourReady;
    bool bDrawWContour;

    CONTOURPHASE contourPhase;
    
    ofTexture loader;
    ofFbo tex;
    ofFbo utilFbo;
    ofPoint pos;
    float rot;
    
    string cmdID;
    vector<ofPolyline> outline;
    deque<ofPolyline> contourForProcess;
    int ptsIdx;
};

#endif /* Painting_hpp */
