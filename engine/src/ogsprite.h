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
	virtual void Render (const OGVec2& _vPos, const OGVec2& _vSize);
		
public:
	struct SprVert
	{
		OGVec2 p;
		OGVec2 t;
    	OGVec4 c;
	};
	SprVert		m_Vertices[4];
	
	IOGRenderer*	m_pRenderer;

	IOGTexture*		m_pTexture;
	IOGMapping*		m_pMapping;
	unsigned int	m_MappingId;
	OGVec4			m_Color;
};


#endif
