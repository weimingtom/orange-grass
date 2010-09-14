/*
 *  OGSpritePool.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSPRITEPOOL_H_
#define OGSPRITEPOOL_H_

#include "IOGSpritePool.h"


class COGSpritePool : public IOGSpritePool
{
public:
	COGSpritePool ();
	virtual ~COGSpritePool ();

	// add sprite.
	virtual void AddSprite (IOGSprite* _pSprite);

	// remove sprite.
	virtual void RemoveSprite (IOGSprite* _pSprite);

private:
};

#endif
