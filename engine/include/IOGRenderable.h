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
    Vec3		    pos;
};


#endif
