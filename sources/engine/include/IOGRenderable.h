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


enum SceneMeshType
{
	OG_SCENEMESH_TERRA				= 0,
	OG_SCENEMESH_SOLID_OBJ			= 1,
	OG_SCENEMESH_TRANSPARENT_OBJ	= 2
};


enum SubMeshType
{
	OG_SUBMESH_BODY			= 0,
	OG_SUBMESH_PROPELLER	= 1,
	OG_SUBMESH_ACTPOINT	    = 2
};


struct IOGActivePoint
{
    std::string     alias;
    OGVec3		    pos;
};


#endif
