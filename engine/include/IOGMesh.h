/*
 *  IOGMesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMESH_H_
#define IOGMESH_H_

#include "Mathematics.h"
#include "IOGAabb.h"
#include <vector>


struct OGFace
{
    Vec3 vertices[3];
    Vec3 normal;
};


class IOGMesh
{
public:
	virtual ~IOGMesh() {}
		
	// Render mesh.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Render part of the mesh.
	virtual void RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame) = 0;

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const = 0;

    // Get num animation frames.
	virtual unsigned int GetNumFrames () const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get part AABB
	virtual const IOGAabb& GetAABB (unsigned int _Part) const = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos) = 0;

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const = 0;
};


#endif
