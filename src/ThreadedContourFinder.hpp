//
//  ThreadedContourFinder.hpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#ifndef ThreadedContourFinder_hpp
#define ThreadedContourFinder_hpp

#include "ofMain.h"
#include "ofxCv.h"
#include "Globals.hpp"

struct DrawCommand
{
    DrawCommand() { numTrial = 0; }
    DrawCommandInfo cmdInfo;
    int numTrial;
};

class ThreadedContourFinder : public ofThread, public ofxCv::ContourFinder
{
public:
    
    ThreadedContourFinder() { startThread(); }
    
protected:
    
    virtual void threadedFunction();
    
private:
    
    void onGenContourEvent(DrawCommandInfo& cmdInfo);

    deque<DrawCommand> commandQ;
};

#endif /* ThreadedContourFinder_hpp */
