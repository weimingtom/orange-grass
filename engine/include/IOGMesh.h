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


class IOGMesh
{
public:
	virtual ~IOGMesh() {}
		
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) = 0;
		
	// Render mesh.
	virtual void Render (const MATRIX& _mView) = 0;

	// Get number of parts
	virtual int GetNumParts () const = 0;

	// Get AABB for the specified part
	virtual const IOGAabb& GetAABB ( int _part ) const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;
};


#endif
