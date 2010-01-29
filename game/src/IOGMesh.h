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


class IOGMesh
{
public:
	virtual ~IOGMesh() {}
		
	// Load mesh.
	virtual bool Load (const char* _pMeshFile) = 0;
		
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) = 0;
		
	// Render mesh.
	virtual void Render (const MATRIX& _mView) = 0;
};


#endif
