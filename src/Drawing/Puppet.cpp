//
//  Puppet.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Puppet.hpp"

void Puppet::setup(string paintingID, ofTexture tex, vector<ofPolyline> lines, ofPoint pos)
{
    this->tex = tex;
    this->pos = pos;
    this->lines = lines;
    scale = 1.0;
    rot = 0.0;
    
    if (!lines.empty())
    {
        ofPolyline line = lines.at(0);
        
        line = line.getResampledBySpacing(20);
        line.getVertices().erase(line.getVertices().begin());
        
        if (line.size() > 5)
        {
            ofPolyline lineForTri = line;
            ofVec2f tweakForDeformer(tex.getWidth()/2, tex.getHeight()/2);
            ofVec2f centroid = lineForTri.getCentroid2D();
            for (auto& p : lineForTri.getVertices())
            {
                // enlarge from centroid
//                ofVec2f dir = (p - centroid).getNormalized();
//                p += dir * 15;
                p -= tweakForDeformer;
            }
            
            mesh.triangulate(lineForTri, 28, -1);
            
            for (auto& v: mesh.triangulatedMesh.getVertices())
            {
                mesh.triangulatedMesh.addTexCoord(tex.getCoordFromPoint(v.x + tweakForDeformer.x,
                                                                        v.y + tweakForDeformer.y));
            }
            
            instance.setup(mesh.triangulatedMesh, lineForTri);
            
            vector<ofPoint> pts = line.getVertices();

            b2dObj = ofPtr<ofxBox2dPolygon>(new ofxBox2dPolygon);
            b2dObj->addVertices(pts);
            b2dObj->setPhysics(1.0, 0.3, 0.3);
            b2dObj->triangulatePoly();
            b2dObj->create(Globals::box2d->getWorld());
            b2dObj->setPosition(pos);
        }
    }
}

void Puppet::update()
{
    instance.update();
}

void Puppet::draw()
{
    ofVec2f rdmPos(ofRandom(-2.5, 2.5), ofRandom(-2.5, 2.5));
    ofVec2f rdmScale(ofRandom(0.95, 1.05), ofRandom(0.95, 1.05));
    
    ofPushMatrix();
    ofTranslate(b2dObj->getPosition() + rdmPos);
    ofScale(rdmScale);
    ofRotate(b2dObj->getRotation(), 0, 0, 1);
    tex.bind();
    instance.getMesh().draw();
    tex.unbind();
    ofPopMatrix();
    
    // debug
//    ofPushMatrix();
//    ofTranslate(600, 500);
//    ofColor c = ofColor::red;
//    int i = 0;
//    for (auto pl : lines)
//    {
//        c.setHueAngle(ofMap(i, 0, lines.size(), 0, 360));
//        ofPushStyle();
//        ofSetColor(c);
//        pl.draw();
//        ofPopStyle();
//        i++;
//    }
//    ofPopMatrix();
//    ofLog() << "num line = " << lines.size();
//    
//    ofPushStyle();
//    ofSetColor(ofColor::red);
//    ofPushMatrix();
//    ofTranslate(b2dObj->getPosition() + rdmPos);
//    ofScale(rdmScale);
//    ofRotate(b2dObj->getRotation(), 0, 0, 1);
//    b2dObj->mesh.drawWireframe();
//    ofPopMatrix();
//    ofPopStyle();
//
//    ofPushStyle();
//    ofSetColor(ofColor::blue);
//    ofPushMatrix();
//    ofTranslate(b2dObj->getPosition() + rdmPos);
//    ofScale(rdmScale);
//    ofRotate(b2dObj->getRotation(), 0, 0, 1);
//    instance.getMesh().drawWireframe();
//    ofPopMatrix();
//    ofPopStyle();
}
