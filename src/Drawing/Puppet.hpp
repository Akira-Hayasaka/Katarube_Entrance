//
//  Puppet.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#ifndef Puppet_hpp
#define Puppet_hpp

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxTriangleMesh.h"
#include "Globals.hpp"
#include "PuppetInstance.hpp"

class Puppet
{
public:
    
    ~Puppet();
    void setup(string paintingID, ofTexture tex, vector<ofPolyline> lines, ofPoint pos);
    void update();
    void draw();
    void register2Box2D();
    
private:
    
    ofTexture tex;
    ofxTriangleMesh mesh;
    ofPoint pos;
    float scale;
    float rot;
    PuppetInstance instance;
    ofPtr<ofxBox2dPolygon> b2dObj;
    
    // debug
    vector<ofPolyline> lines;
};

#endif /* Puppet_hpp */
