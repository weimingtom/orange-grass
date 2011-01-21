/*
 *  ogsprite.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogsprite.h"
#include "OrangeGrass.h"


static int m_HalfScrWidth = 0;
static int m_HalfScrHeight = 0;


COGSprite::COGSprite() :	m_pTexture(NULL),
							m_pMapping(NULL),
							m_MappingId(0)
{
	m_pRenderer = GetRenderer();
	m_HalfScrWidth = GetGlobalVars()->GetIVar("view_width") / 2;
	m_HalfScrHeight = GetGlobalVars()->GetIVar("view_height") / 2;
	m_Color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
}


COGSprite::~COGSprite()
{
	m_pTexture = NULL;
	m_pMapping = NULL;
	m_MappingId = 0;
}


// Initialize sprite.
void COGSprite::SetMapping (unsigned int _Mapping)
{
	m_MappingId = _Mapping;
}


// Load resource.
bool COGSprite::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    

    case OG_RESSTATE_DEFINED:
        break;
	}

	m_pTexture = GetResourceMgr()->GetTexture(m_ResourcePool, m_ResourceFile);
	if (m_pTexture)
	{
		m_pMapping = m_pTexture->GetMapping(m_MappingId);
		if (!m_pMapping)
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	m_LoadState = OG_RESSTATE_LOADED;
    return true;
}


// Unload resource.
void COGSprite::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	m_pTexture = NULL;
	m_pMapping = NULL;

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render sprite.
void COGSprite::Render (const Vec2& _vPos, const Vec2& _vSize)
{
	float fLeft = -m_HalfScrWidth+_vPos.x;
	float fRight = -m_HalfScrWidth+_vSize.x+_vPos.x;
	float fTop = m_HalfScrHeight-_vSize.y-_vPos.y;
	float fBottom = m_HalfScrHeight-_vPos.y;

	m_Vertices[0].p	= Vec2(fRight, fTop);	
	m_Vertices[0].t = Vec2(m_pMapping->t1.x, m_pMapping->t0.y); 
	m_Vertices[0].c = m_Color;
	m_Vertices[1].p	= Vec2(fLeft, fTop);	
	m_Vertices[1].t = Vec2(m_pMapping->t0.x, m_pMapping->t0.y); 
	m_Vertices[1].c = m_Color;
	m_Vertices[2].p	= Vec2(fRight, fBottom);	
	m_Vertices[2].t = Vec2(m_pMapping->t1.x, m_pMapping->t1.y); 
	m_Vertices[2].c = m_Color;
	m_Vertices[3].p	= Vec2(fLeft, fBottom);	
	m_Vertices[3].t = Vec2(m_pMapping->t0.x, m_pMapping->t1.y); 
	m_Vertices[3].c = m_Color;

	m_pRenderer->SetTexture(m_pTexture);
    m_pRenderer->DrawSpriteBuffer(m_Vertices, 0, 4);
}
