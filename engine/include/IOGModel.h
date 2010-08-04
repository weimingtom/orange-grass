/*
 *  IOGModel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMODEL_H_
#define IOGMODEL_H_

#include "IOGRenderable.h"
#include "IOGTexture.h"
#include "IOGMesh.h"


class IOGModel : public IOGRenderable
{
public:
	virtual ~IOGModel() {}

	// Render mesh.
	virtual void Render (const MATRIX& _mView) = 0;

	// Render.
	virtual void Render (const MATRIX& _mView, unsigned int _Part) = 0;

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const = 0;

	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get model alias
	virtual const char* GetAlias () const = 0;
};


#endif
