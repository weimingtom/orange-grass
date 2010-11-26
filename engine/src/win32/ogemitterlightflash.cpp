/*
 *  ogemitterlightflash.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterlightflash.h"
#include "OrangeGrass.h"


COGEmitterLightFlash::COGEmitterLightFlash()
{
}


COGEmitterLightFlash::~COGEmitterLightFlash()
{
}


// Initialize emitter.
void COGEmitterLightFlash::Init()
{
	m_color = Vec4(1, 1, 0, 1);
	m_bPositionUpdated = false;
	m_pLight = NULL;
}


// Update.
void COGEmitterLightFlash::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    if (m_pLight)
    {
		if (m_pLight->fIntensity >= m_fFadeFactor)
		{
			m_pLight->fIntensity -= m_fFadeFactor;
		}
		else
		{
			Stop();
		}
    }
}


// Render.
void COGEmitterLightFlash::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    if (m_pLight)
    {
        m_pLight->vPosition = vOffset;
    }
}


// Start.
void COGEmitterLightFlash::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

	if (m_pLight)
    {
        m_pRenderer->GetLightMgr()->DestroyLight(m_pLight);
        m_pLight = NULL;
    }

	m_pLight = m_pRenderer->GetLightMgr()->CreateLight();

	if (m_pLight)
    {
        m_pLight->vDiffuseColor = m_color;
        m_pLight->vSpecularColor = m_color;
        m_pLight->vAmbientColor = m_color;
        m_pLight->type = OG_LIGHT_POINT;
        m_pLight->fIntensity = m_fInitialIntensity;
    }
}


// Stop.
void COGEmitterLightFlash::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (m_pLight)
    {
        m_pRenderer->GetLightMgr()->DestroyLight(m_pLight);
        m_pLight = NULL;
    }

	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
