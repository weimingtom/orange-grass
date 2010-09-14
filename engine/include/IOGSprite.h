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
#include "Mathematics.h"


class IOGSprite
{
public:
	virtual ~IOGSprite() {}
		
	// Initialize sprite.
	virtual void SetMapping (const Vec2& _vT0, const Vec2& _vT1) = 0;
		
	// Render sprite.
	virtual void Render (const Vec2& _vPos, const Vec2& _vSize) = 0;
};


#endif
