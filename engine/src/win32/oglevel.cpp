/*
 *  OGLevel.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "orangegrass.h"
#include "oglevel.h"


COGLevel::COGLevel () : m_pTerrain(NULL)
{
}


COGLevel::~COGLevel ()
{
    if (m_pTerrain)
    {
    }
    m_pTerrain = NULL;
}


// load scene from file.
bool COGLevel::Load ()
{
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

    m_pTerrain = GetResourceMgr()->GetTerrain(m_pResourceAlias);
    if (m_pTerrain == NULL)
        return false;

	m_LoadState = OG_RESSTATE_LOADED;
    return true;    
}


// get associated terrain.
IOGTerrain* COGLevel::GetTerrain ()
{
    return m_pTerrain;
}
