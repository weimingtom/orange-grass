/*
 *  IOGModel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMESH_H_
#define IOGMESH_H_

#include "IOGGeometry.h"
#include "IOGVertexBuffers.h"
#include <vector>


struct OGSubMesh
{
    unsigned int        part;
    SubMeshType         type;
    std::string         name;
    IOGAabb*            aabb;
    IOGVertexBuffers*   buffer;
};


class IOGMesh
{
public:
	virtual ~IOGMesh() {}

    // Get list of all submeshes
    virtual const std::vector<OGSubMesh>& GetSubMeshes () const = 0;

    // Update submesh (for tools)
    virtual void UpdateSubMesh (unsigned int _Id, const OGSubMesh& _SubMesh) = 0;

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const = 0;

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const = 0;
};

#endif