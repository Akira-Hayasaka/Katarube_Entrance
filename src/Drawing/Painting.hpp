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
        END,
        GENPUPPET
    };
    
    void setup(string texPath, bool bNeedContour = false, bool bForPuppet = false);
    void update();
    void draw();
    void drawOutline();
    void fadeOut();
    
    void setPosition(ofPoint pos) { this->pos = pos; }
    void setRot(float rot) { this->rot = rot; }
    ofTexture& getTexture() { return tex.getTexture(); }
    ofPixels getPixels() { return px; }
    vector<ofPolyline> getOutlines() { return outline; }
    string getID() { return paintingID; }
    ofPoint getPosition() { return pos; }
    void beginDraw();
    bool isFinished() { return (phase == END) ? true : false; }
    void markGenPuppet() { phase = GENPUPPET; }
    bool isGenPuppet() { return (phase == GENPUPPET) ? true : false; }
    
private:
    
    bool bNeedContour;
    bool bContourReady;
    
    PHASE phase;
    
    string paintingID;
    
    ofFbo tex;
    ofPixels px;    
    ofFbo utilFbo;
    ofPoint pos;
    float rot;
    float scale;
    
    string cmdID;
    vector<ofPolyline> outline;
    vector<ofPolyline> contourWHoles;
    deque<ofPolyline> contourForProcess;
    int ptsIdx;
    
    float beginDrawWContourTime;
    float waitHandDur;
};

#endif /* Painting_hpp */