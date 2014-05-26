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
