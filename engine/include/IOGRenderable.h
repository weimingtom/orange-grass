/*
 *  IOGRenderable.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGRENDERABLE_H_
#define IOGRENDERABLE_H_

#include "IOGAabb.h"


// Type of the renderables
enum RenderableType
{
	OG_RENDERABLE_MODEL,
	OG_RENDERABLE_TERRAIN,
};


// Base renderable object interface.
class IOGRenderable
{
public:
	// destructor
	virtual ~IOGRenderable () {}

	// Render.
	virtual void Render (const MATRIX& _mView) = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const = 0;
};

#endif
