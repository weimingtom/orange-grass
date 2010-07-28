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
	
	// Set terrain position.
	virtual void SetWorldPosition (const Vec3& _vPos) = 0;
};


#endif