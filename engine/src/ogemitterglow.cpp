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


std::string COGEmitterGlow::s_Alias = std::string("glow");
OGEmitterType COGEmitterGlow::s_Type = OG_EMITTER_GLOW;


COGEmitterGlow::COGEmitterGlow()
{
	m_Texture = std::string("effects");
	m_MappingId = 9;
	m_fInitialScale = 2.0f;
	m_fInitialAngleMin = -3.14f;
	m_fInitialAngleMax = 3.14f;
	m_color = Vec4(1.0f, 1.0f, 1.0f, 0.6f);

	AddStringParam("texture", &m_Texture);
	AddIntParam("mapping", &m_MappingId);
	AddFloatParam("init_angle_min", &m_fInitialAngleMin);
	AddFloatParam("init_angle_max", &m_fInitialAngleMax);
	AddFloatParam("init_scale", &m_fInitialScale);
	AddColorParam("color", &m_color);
}


COGEmitterGlow::~COGEmitterGlow()
{
}


// Initialize emitter.
void COGEmitterGlow::Init (IOGGroupNode* _pNode)
{
	LoadParams(_pNode);

	m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAONE;

	m_Glow.scale = m_fInitialScale;
	m_Glow.angle = GetRandomRange(
		(int)(m_fInitialAngleMin * 100.0f), 
		(int)(m_fInitialAngleMax * 100.0f)) * 0.01f;
	m_Glow.pVertices[0].c = m_color;
	m_Glow.pVertices[1].c = m_color;
	m_Glow.pVertices[2].c = m_color;
	m_Glow.pVertices[3].c = m_color;

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
