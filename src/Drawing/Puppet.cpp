//
//  Puppet.cpp
//  Entrance
//
//  Created by Akira Hayasaka on 7/6/16.
//
//

#include "Puppet.hpp"

void Puppet::setup(string texPath,
                   bool bNeedContour, bool bConstrainSize)
{
    Painting::setup(texPath, bNeedContour, bConstrainSize);
    
    bRegisterBox2d = false;
    state = INIT;
}

void Puppet::update()
{
    Painting::update();
    
    if (bContourReady && !bRegisterBox2d)
    {
        vector<ofPolyline> lines = outlineOriginal;
        
        if (!lines.empty())
        {
            ofPolyline line = lines.at(0);
            
            line = line.getResampledBySpacing(20);
            line.getVertices().erase(line.getVertices().begin());
            
            if (line.size() > 5)
            {
                ofxTriangleMesh mesh;
                mesh.triangulate(line, 28, -1);
                
                for (auto& v: mesh.triangulatedMesh.getVertices())
                {
                    mesh.triangulatedMesh.addTexCoord(tex.getTexture().getCoordFromPoint(v.x, v.y));
                }
                
                instance.setup(mesh.triangulatedMesh, line);
                instance.setPosition(200, 200, 0);
                
                state = READY;
            }
        }
        
        bRegisterBox2d = true;
    }
}