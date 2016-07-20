//
//  ThreadedContourFinder.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/17/16.
//
//

#include "ThreadedContourFinder.hpp"

void ThreadedContourFinder::setup()
{
    ofAddListener(Globals::genContourEvent, this, &ThreadedContourFinder::onGenContourEvent);
    startThread();
}

void ThreadedContourFinder::threadedFunction()
{
    while (isThreadRunning())
    {
        lock();
        if (!commandQ.empty())
        {
            if (commandQ.front().numTrial < 5)
            {
                setMinAreaRadius(commandQ.front().cmdInfo.contourMinArea);
                setMaxAreaRadius(commandQ.front().cmdInfo.contourMaxArea);
                setThreshold(commandQ.front().cmdInfo.contourBriThresh);
                findContours(commandQ.front().cmdInfo.px);
                commandQ.front().numTrial++;
            }
            else
            {
                DrawCommandContour cc;
                cc.cmdID = commandQ.front().cmdInfo.cmdID;
                setFindHoles(false);
                cc.contours = getPolylines();
                ofNotifyEvent(Globals::gotContourEvent, cc);
                
                DrawCommandContour ccHole;
                ccHole.cmdID = commandQ.front().cmdInfo.cmdID;
                setFindHoles(true);
                ccHole.contours = getPolylines();
                ofNotifyEvent(Globals::gotContourWHoleEvent, ccHole);
                
                commandQ.pop_front();
            }
        }
        unlock();
        
        ofSleepMillis(1000 * 0.2);
    }
}

void ThreadedContourFinder::onGenContourEvent(DrawCommandInfo& cmdInfo)
{
    DrawCommand dc;
    dc.cmdInfo = cmdInfo;
    
    lock();
    commandQ.push_back(dc);
    unlock();
}