/*
 *  IOGTerrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGTERRAIN_H_
#define IOGTERRAIN_H_

#include "IOGRenderable.h"
#include "IOGTexture.h"
#include "IOGMesh.h"


class IOGTerrain : public IOGRenderable
{
public:
	virtual ~IOGTerrain() {}

	// Render mesh.
	virtual void Render (const MATRIX& _mView) = 0;

	// Render.
	virtual void Render (const MATRIX& _mView, unsigned int _Part) = 0;

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const = 0;
	
	// Set terrain position.
	virtual void SetWorldPosition (const Vec3& _vPos) = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos) = 0;

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;
};


#endif