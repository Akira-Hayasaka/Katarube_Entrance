//
//  Warper.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 6/23/16.
//
//

#include "Warper.hpp"

void Warper::setup()
{
    ofxQuadWarp::setup();
    
    ofRectangle r;
    r.set(getTargetPoints()[0].x, getTargetPoints()[0].y,
          getTargetPoints()[2].x - getTargetPoints()[0].x, getTargetPoints()[2].y - getTargetPoints()[0].y);
    dstCenter = r.getCenter();
}

void Warper::update()
{
    if (bShow == false)
        return;
    
    vector<ofPoint> dstPts(getTargetPoints(), getTargetPoints()+4);
    for (auto& p : dstPts)
        p = (1.0/WARP_TWEAK_SCALE) * (p - dstCenter) + dstCenter;
    scaledMat = getMatrix(getSourcePoints(), &dstPts[0]);
}