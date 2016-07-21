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
#include "Painting.hpp"
#include "ofxTriangleMesh.h"
#include "PuppetInstance.hpp"

class Puppet : public Painting
{
public:
    
    void setup(string texPath,
               bool bNeedContour = false, bool bConstrainSize = false);
    void update();
    
private:
    
    enum STATE
    {
        INIT,
        READY,
        RUN
    };
    STATE state;
    
    bool bRegisterBox2d;
    
    PuppetInstance instance;
};

#endif /* Puppet_hpp */
