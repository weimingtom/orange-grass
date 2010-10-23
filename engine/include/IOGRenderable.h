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
#include "IOGAnimation.h"
#include <string>


// Type of the renderables
enum RenderableType
{
	OG_RENDERABLE_MODEL,
	OG_RENDERABLE_TERRAIN,
	OG_RENDERABLE_EFFECT,
};


struct IOGActivePoint
{
	std::string     alias;
    MATRIX          mLocalTM;
    unsigned int    id;
	Vec3		    pos;
};


// Base renderable object interface.
class IOGRenderable
{
public:
	// destructor
	virtual ~IOGRenderable () {}

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame) = 0;

	// Render all.
	virtual void RenderAll (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Update.
	virtual void Update (unsigned long _ElapsedTime) = 0;

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const = 0;

	// Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) = 0;

	// Get active point
	virtual bool GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame) = 0;
};

#endif
