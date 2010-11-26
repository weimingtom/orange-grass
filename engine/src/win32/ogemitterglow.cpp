/*
 *  ogemitterglow.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterglow.h"
#include "OrangeGrass.h"


COGEmitterGlow::COGEmitterGlow()
{
}


COGEmitterGlow::~COGEmitterGlow()
{
}


// Initialize emitter.
void COGEmitterGlow::Init()
{
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAADD;

	m_Glow.bDirty = false;
	m_Glow.scale = 2.0f;
	m_Glow.angle = GetRandomRange(-314,314) * 0.01f;
	m_Glow.pVertices[0].c = Vec4(1.0f,1.0f,1.0f,0.6f);
	m_Glow.pVertices[1].c = Vec4(1.0f,1.0f,1.0f,0.6f);
	m_Glow.pVertices[2].c = Vec4(1.0f,1.0f,1.0f,0.6f);
	m_Glow.pVertices[3].c = Vec4(1.0f,1.0f,1.0f,0.6f);

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterGlow::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;
}


// Render.
void COGEmitterGlow::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    if (m_Status != OG_EFFECTSTATUS_STOPPED)
    {
		MATRIX mR;
        MatrixRotationAxis(mR, m_Glow.angle, _vLook.x, _vLook.y, _vLook.z);

        Vec3 vSUp = _vUp * m_Glow.scale;
        Vec3 vSRight = _vRight * m_Glow.scale;

		BBVert* pVert = NULL;
        pVert = &m_Glow.pVertices[0];
        MatrixVecMultiply(pVert->p, vSRight + vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t0.y;

        pVert = &m_Glow.pVertices[1];
        MatrixVecMultiply(pVert->p, -vSRight + vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t0.y;

        pVert = &m_Glow.pVertices[2];
        MatrixVecMultiply(pVert->p, vSRight - vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t1.y;

        pVert = &m_Glow.pVertices[3];
        MatrixVecMultiply(pVert->p, -vSRight - vSUp, mR);
        pVert->p += m_vCurPosition;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t1.y;

        m_pRenderer->DrawEffectBuffer(&m_Glow.pVertices[0], 0, 4);
    }
}


// Start.
void COGEmitterGlow::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEmitterGlow::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
