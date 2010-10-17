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


COGEffect::COGEffect()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_pRenderer = GetRenderer();
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
}


// Render.
void COGEffect::Render (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame)
{
    Render(_mWorld, _Frame);
}


// Start.
void COGEffect::Start ()
{
}


// Stop.
void COGEffect::Stop ()
{
}
