//
//  PuppetInstance.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/21/16.
//
//

#include "PuppetInstance.hpp"

void PuppetInstance::setup(ofMesh mesh, ofPolyline outline)
{
    this->outline = outline.getResampledByCount(20);
    //    this->outline.simplify(1.2);
    deformer.setup(mesh);
    buildDeformPts();
}

void PuppetInstance::update()
{
    animateMesh();
    deformer.update();
}

void PuppetInstance::customDraw()
{
    deformer.getDeformedMesh().draw();
    debugDrawCtrlPts();
}

void PuppetInstance::buildDeformPts()
{
    ofMesh mesh = deformer.getOriginalMesh();
    ofPoint center = mesh.getCentroid();
    
    // fix center;
    vector<IdxDist> centerCandidates;
    for (int i = 0; i < mesh.getVertices().size(); i++)
    {
        IdxDist idist;
        idist.idx = i;
        idist.dist = mesh.getVertices().at(i).distance(center);
        centerCandidates.push_back(idist);
    }
    ofSort(centerCandidates, compDistance);
    deformer.setControlPoint(centerCandidates.back().idx);
    
    // get edge
    vector<IdxAngle> iAngles;
    vector<ofPoint> pts = outline.getVertices();
    for (int i = 0; i < pts.size(); i++)
    {
        ofPoint cur = pts.at(i);
        ofPoint next;
        if (i >= pts.size()-1)
            next = pts.at(0);
        else
            next = pts.at(i + 1);
        float ang = cur.angleRad(next);
        int idx = 0;
        float dist = getNearestVertex(mesh, next, idx);
        IdxAngle iAng;
        iAng.idx = idx;
        iAng.ang = ang;
        iAngles.push_back(iAng);
    }
    ofSort(iAngles, compAngle);
    
    for (int i = 0; i < 4; i++)
        deformIdxs.push_back(iAngles.at(i).idx);
    
    //    vector<IdxDist> leftEdges;
    //    vector<IdxDist> rightEdges;
    //    vector<IdxDist> topEdges;
    //    vector<IdxDist> bottomEdges;
    //    for (int i = 0; i < mesh.getVertices().size(); i++)
    //    {
    //        IdxDist idist;
    //        idist.idx = i;
    //
    //        // left
    //        if (mesh.getVertices().at(i).x < center.x)
    //        {
    //            idist.dist = fabs(mesh.getVertices().at(i).x - center.x);
    //            leftEdges.push_back(idist);
    //        }
    //        // right
    //        else
    //        {
    //            idist.dist = fabs(mesh.getVertices().at(i).x - center.x);
    //            rightEdges.push_back(idist);
    //        }
    //
    //        // top
    //        if (mesh.getVertices().at(i).y < center.y)
    //        {
    //            idist.dist = fabs(mesh.getVertices().at(i).y - center.y);
    //            topEdges.push_back(idist);
    //        }
    //        // bottom
    //        else
    //        {
    //            idist.dist = fabs(mesh.getVertices().at(i).y - center.y);
    //            bottomEdges.push_back(idist);
    //        }
    //    }
    ////    ofSort(leftEdges, compDistance);
    ////    ofSort(rightEdges, compDistance);
    //    ofSort(topEdges, compDistance);
    //    ofSort(bottomEdges, compDistance);
    //    ofRandomize(leftEdges);
    //    ofRandomize(rightEdges);
    ////    ofRandomize(topEdges);
    ////    ofRandomize(bottomEdges);
    //
    //    if (leftEdges.size() > 2)
    //        for (int i = 0; i < 2; i++)
    //            deformIdxsLeft.push_back(leftEdges.at(i).idx);
    //
    //    if (rightEdges.size() > 2)
    //        for (int i = 0; i < 2; i++)
    //            deformIdxsRight.push_back(rightEdges.at(i).idx);
    //
    //    if (topEdges.size() > 2)
    //        for (int i = 0; i < 2; i++)
    //            deformIdxsTop.push_back(topEdges.at(i).idx);
    //
    //    if (bottomEdges.size() > 2)
    //        for (int i = 0; i < 2; i++)
    //            deformIdxsBottom.push_back(bottomEdges.at(i).idx);
}

void PuppetInstance::animateMesh()
{
    int phase = 0;
    float speed = 3.1;
    float amt = 0.25;
    float yn = ofSignedNoise(phase, TWO_PI, ofGetElapsedTimef() * speed) * amt;
    
    for (auto idx : deformIdxsLeft)
    {
        ofVec3f vert = deformer.getDeformedMesh().getVertices().at(idx);
        vert += ofVec3f(0.0, yn, 0.0);
        deformer.setControlPoint(idx, vert);
    }
    phase++;
    
    speed = 3.1;
    amt = 0.25;
    yn = ofSignedNoise(phase, TWO_PI, ofGetElapsedTimef() * speed) * amt;
    for (auto idx : deformIdxsRight)
    {
        ofVec3f vert = deformer.getDeformedMesh().getVertices().at(idx);
        vert += ofVec3f(0.0, yn, 0.0);
        deformer.setControlPoint(idx, vert);
    }
    phase++;
    
    speed = 1.5;
    amt = 80.0;
    yn = ofNoise(phase, TWO_PI, ofGetElapsedTimef() * speed) * amt * -1.0;
    for (auto idx : deformIdxsTop)
    {
        ofVec3f vert = deformer.getOriginalMesh().getVertices().at(idx);
        vert += ofVec3f(0.0, yn, 0.0);
        deformer.setControlPoint(idx, vert);
    }
    phase++;
    
    speed = 2.5;
    amt = 5.0;
    float xn = ofSignedNoise(phase, TWO_PI, ofGetElapsedTimef() * speed) * amt;
    for (auto idx : deformIdxsBottom)
    {
        ofVec3f vert = deformer.getDeformedMesh().getVertices().at(idx);
        vert += ofVec3f(xn, 0.0, 0.0);
        deformer.setControlPoint(idx, vert);
    }
    phase++;
}

void PuppetInstance::debugDrawCtrlPts()
{
    ofPushStyle();
    ofFill();
    ofSetColor(ofColor::red);
    for (auto idx : deformIdxs)
        ofDrawCircle(deformer.getDeformedMesh().getVertices().at(idx), 2);
    ofNoFill();
    ofSetColor(ofColor::cyan);
    for (auto idx : deformIdxsLeft)
        ofDrawCircle(deformer.getDeformedMesh().getVertices().at(idx), 10);
    ofSetColor(ofColor::magenta);
    for (auto idx : deformIdxsRight)
        ofDrawCircle(deformer.getDeformedMesh().getVertices().at(idx), 10);
    ofSetColor(ofColor::yellow);
    for (auto idx : deformIdxsTop)
        ofDrawCircle(deformer.getDeformedMesh().getVertices().at(idx), 10);
    ofSetColor(ofColor::green);
    for (auto idx : deformIdxsBottom)
        ofDrawCircle(deformer.getDeformedMesh().getVertices().at(idx), 10);
    ofSetColor(ofColor::skyBlue);
    outline.draw();
    ofPopStyle();
}

float PuppetInstance::getNearestVertex(const ofMesh& mesh, const ofVec2f& target, int& vertexIndex)
{
    float bestDistance = 0;
    for (int i = 0; i < mesh.getNumVertices(); i++)
    {
        float distance = target.distance(mesh.getVertex(i));
        if (distance < bestDistance || i == 0)
        {
            bestDistance = distance;
            vertexIndex = i;
        }
    }
    return bestDistance;
}