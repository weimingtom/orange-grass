/*
 *  ogsprite.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSPRITE_H_
#define OGSPRITE_H_

#include "IOGSprite.h"
#include "ogresource.h"


class COGSprite : public IOGSprite, public COGResource
{
public:
	COGSprite();
	virtual ~COGSprite();
		
	// Initialize sprite.
	virtual void SetMapping (const Vec2& _vT0, const Vec2& _vT1);

    // Load resource.
    virtual bool Load ();

	// Unload resource.
	virtual void Unload ();
	
	// Render sprite.
	virtual void Render (const Vec2& _vPos, const Vec2& _vSize);
		
public:
	struct SprVert
	{
		Vec2 p;
		Vec2 t;
	};
	SprVert		m_Vertices[4];
	
	IOGTexture*	m_pTexture;
	Vec2		m_T0;
	Vec2		m_T1;
	Vec2		m_Pos;
	Vec2		m_Size;
};


#endif
