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
#include "IOGRenderer.h"


class COGSprite : public IOGSprite, public COGResource
{
public:
	COGSprite();
	virtual ~COGSprite();

	// Initialize sprite.
	virtual void SetMapping (unsigned int _Mapping);

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
    	Vec4 c;
	};
	SprVert		m_Vertices[4];
	
	IOGRenderer*	m_pRenderer;

	IOGTexture*		m_pTexture;
	IOGMapping*		m_pMapping;
	unsigned int	m_MappingId;
	Vec4			m_Color;
};


#endif
