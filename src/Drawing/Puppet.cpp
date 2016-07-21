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
            for (auto& p : lineForTri.getVertices())
            {
                p.x -= tex.getWidth()/2;
                p.y -= tex.getHeight()/2;
            }
            
            mesh.triangulate(lineForTri, 28, -1);
            
            for (auto& v: mesh.triangulatedMesh.getVertices())
            {
                mesh.triangulatedMesh.addTexCoord(tex.getCoordFromPoint(v.x + tex.getWidth()/2,
                                                                        v.y + tex.getHeight()/2));
            }
            
            instance.setup(mesh.triangulatedMesh, lineForTri);
            
            vector<ofPoint> pts = line.getVertices();

            b2dObj = ofPtr<ofxBox2dPolygon>(new ofxBox2dPolygon);
            b2dObj->addVertices(pts);
            b2dObj->setPhysics(3.0, 0.53, 0.1);
            b2dObj->triangulatePoly();
            b2dObj->create(Globals::box2d.getWorld());
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
    ofPushMatrix();
    ofTranslate(b2dObj->getPosition());
    ofRotate(b2dObj->getRotation(), 0, 0, 1);
    tex.bind();
    instance.getMesh().draw();
    tex.unbind();
    ofPopMatrix();
}
