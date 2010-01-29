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


class IOGSprite
{
public:
	virtual ~IOGSprite() {}
		
	// Initialize sprite.
	virtual void Init (IOGTexture* _pTexture) = 0;
		
	// Set position.
	virtual void SetPosition (float _fX, float _fY, float _fWidth, float _fHeight) = 0;
		
	// Render sprite.
	virtual void Render () = 0;
};


#endif
