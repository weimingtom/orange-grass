/*
 *  IOGTexture.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGTEXTURE_H_
#define IOGTEXTURE_H_

#include "Mathematics.h"


struct IOGMapping
{
	Vec2 t0;
	Vec2 t1;
	Vec2 upper_left;
	Vec2 size;
};

class IOGTexture
{
public:
	virtual ~IOGTexture () {}
		
	// get gl texture id
	virtual unsigned int GetTextureId () const = 0;
		
	// apply texture
	virtual void Apply () const = 0;

	// get texture mapping
	virtual IOGMapping* GetMapping (unsigned int _Id) = 0;
	
	// get texture width
	virtual unsigned int GetWidth () const = 0;
	
	// get texture height
	virtual unsigned int GetHeight () const = 0;
};

#endif
