/*
 *  IOGSprite.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGSPRITE_H_
#define IOGSPRITE_H_

#include "IOGTexture.h"
#include "IOGMath.h"


class IOGSprite
{
public:
	virtual ~IOGSprite() {}

	// Initialize sprite.
	virtual void SetMapping (unsigned int _Mapping) = 0;
		
	// Render sprite.
	virtual void Render (const OGVec2& _vPos, const OGVec2& _vSize) = 0;
};


#endif
