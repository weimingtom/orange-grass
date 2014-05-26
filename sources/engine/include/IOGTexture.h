/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef IOGTEXTURE_H_
#define IOGTEXTURE_H_

#include "IOGVector.h"

struct IOGMapping
{
	OGVec2 t0;
	OGVec2 t1;
	OGVec2 upper_left;
	OGVec2 size;
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
