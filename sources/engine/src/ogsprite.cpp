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
    m_Color = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);
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
void COGSprite::Render (const OGVec2& _vPos, const OGVec2& _vSize)
{
    //float fLeft = -m_HalfScrWidth+_vPos.x;
    //float fRight = -m_HalfScrWidth+_vSize.x+_vPos.x;
    //float fTop = m_HalfScrHeight-_vSize.y-_vPos.y;
    //float fBottom = m_HalfScrHeight-_vPos.y;

    //m_Vertices[0].p	= OGVec2(fRight, fTop);	
    //m_Vertices[0].t = OGVec2(m_pMapping->t1.x, m_pMapping->t0.y); 
    //m_Vertices[0].c = m_Color;
    //m_Vertices[1].p	= OGVec2(fLeft, fTop);	
    //m_Vertices[1].t = OGVec2(m_pMapping->t0.x, m_pMapping->t0.y); 
    //m_Vertices[1].c = m_Color;
    //m_Vertices[2].p	= OGVec2(fRight, fBottom);	
    //m_Vertices[2].t = OGVec2(m_pMapping->t1.x, m_pMapping->t1.y); 
    //m_Vertices[2].c = m_Color;
    //m_Vertices[3].p	= OGVec2(fLeft, fBottom);	
    //m_Vertices[3].t = OGVec2(m_pMapping->t0.x, m_pMapping->t1.y); 
    //m_Vertices[3].c = m_Color;

    //m_pRenderer->SetTexture(m_pTexture);
    //m_pRenderer->DrawSpriteBuffer(m_Vertices, 0, 4);
}
