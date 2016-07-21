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
#include "ofxTweenzor.h"
#include "Globals.hpp"
#include "Util.h"

static bool compareLeft2Right(const ofPolyline& p1, const ofPolyline& p2)
{
    return p1.getCentroid2D().x < p2.getCentroid2D().x;
}

class Painting
{
public:
    
    enum PHASE
    {
        NONE,
        WAITINGHAND,
        DRAWING,
        END
    };
    
    void setup(string texPath, bool bNeedContour = false);
    void update();
    void draw();
    void drawOutline();
    void fadeOut();
    
    void setPosition(ofPoint pos) { this->pos = pos; }
    void setRot(float rot) { this->rot = rot; }
    ofTexture& getTexture() { return tex.getTexture(); }
    void beginDraw();
    
private:
    
    void onGotContourEvent(DrawCommandContour& cc);
    
    bool bNeedContour;
    bool bContourReady;

    PHASE phase;
    
    ofFbo tex;
    ofFbo utilFbo;
    ofPoint pos;
    float rot;
    float scale;
    
    string cmdID;
    vector<ofPolyline> outline;
    deque<ofPolyline> contourForProcess;
    int ptsIdx;
    
    float beginDrawWContourTime;
    float waitHandDur;
};

#endif /* Painting_hpp */
