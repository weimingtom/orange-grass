/*
 *  ogemitter.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitter.h"
#include "OrangeGrass.h"


COGEmitter::COGEmitter()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_pRenderer = GetRenderer();
}


COGEmitter::~COGEmitter()
{
}


// Update position.
void COGEmitter::UpdatePosition (const Vec3& _vPosition)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (!m_bPositionUpdated)
	{
		m_vCurPosition = _vPosition;
		m_vPrevPosition = _vPosition;
		m_bPositionUpdated = true;
	}
	else
	{
		m_vPrevPosition = m_vCurPosition;
		m_vCurPosition = _vPosition;
	}
}


// Get effect run status.
OGEffectStatus COGEmitter::GetStatus() const 
{ 
	return m_Status; 
}
