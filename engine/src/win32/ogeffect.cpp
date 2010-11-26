/*
 *  ogeffect.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffect.h"
#include "OrangeGrass.h"


COGEffect::COGEffect() :	m_pTexture(NULL)
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_pRenderer = GetRenderer();
	m_bPositionUpdated = false;
}


COGEffect::~COGEffect()
{
}


// Set billboard basis vectors.
void COGEffect::SetBillboardVectors (const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
    m_vCameraLook = _vLook;
	m_vCameraUp = _vUp;
	m_vCameraRight = _vRight;
}


// Set direction.
void COGEffect::SetDirection (const Vec3& _vDir)
{
	m_Direction = _vDir;
}


// Update position.
void COGEffect::UpdatePosition (const Vec3& _vPosition)
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


// Start.
void COGEffect::Start ()
{
}


// Stop.
void COGEffect::Stop ()
{
}
