//
//  PuppetInstance.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/21/16.
//
//

#ifndef PuppetInstance_hpp
#define PuppetInstance_hpp

#include "ofMain.h"
#include "ofxPuppetInteractive.h"

struct IdxDist
{
    int idx;
    float dist;
};

struct IdxAngle
{
    int idx;
    float ang;
};

static bool compDistance(const IdxDist& p1, const IdxDist& p2)
{
    return p1.dist > p2.dist;
}

static bool compAngle(const IdxAngle& p1, const IdxAngle& p2)
{
    return p1.ang < p2.ang;
}

class PuppetInstance : public ofNode
{
public:
    
    void setup(ofMesh mesh, ofPolyline outline);
    void update();
    void customDraw();
    
private:
    
    void buildDeformPts();
    void animateMesh();
    void debugDrawCtrlPts();
    float getNearestVertex(const ofMesh& mesh, const ofVec2f& target, int& vertexIndex);
    
    ofxPuppetInteractive deformer;
    ofPolyline outline;
    
    vector<int> deformIdxs;
    vector<int> deformIdxsLeft;
    vector<int> deformIdxsRight;
    vector<int> deformIdxsTop;
    vector<int> deformIdxsBottom;
};

#endif /* PuppetInstance_hpp */
