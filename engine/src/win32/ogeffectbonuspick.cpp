/*
 *  ogeffectbonuspick.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectbonuspick.h"
#include "OrangeGrass.h"


COGEffectBonusPick::~COGEffectBonusPick()
{
}


// Initialize effect.
void COGEffectBonusPick::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture("explosion");
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_WaveMapping = *m_pTexture->GetMapping(10);
    m_Wave.scale = 8.0f;
    m_Wave.angle = 0.0f;
    m_Wave.offset = Vec3(0,0,0);
    m_Wave.pVertices[0].c = color;
    m_Wave.pVertices[0].t = Vec2(m_WaveMapping.t1.x, m_WaveMapping.t0.y);
    m_Wave.pVertices[1].c = color;
    m_Wave.pVertices[1].t = Vec2(m_WaveMapping.t0.x, m_WaveMapping.t0.y);
    m_Wave.pVertices[2].c = color;
    m_Wave.pVertices[2].t = Vec2(m_WaveMapping.t1.x, m_WaveMapping.t1.y);
    m_Wave.pVertices[3].c = color;
    m_Wave.pVertices[3].t = Vec2(m_WaveMapping.t0.x, m_WaveMapping.t1.y);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectBonusPick::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	float fAlphaInc = 0.08f;
	float fScaleInc = 1.5f;

    if (m_Wave.pVertices[0].c.w >= fAlphaInc)
    {
        m_Wave.scale += fScaleInc;
        m_Wave.pVertices[0].c.w -= fAlphaInc;
        m_Wave.pVertices[1].c.w -= fAlphaInc;
        m_Wave.pVertices[2].c.w -= fAlphaInc;
        m_Wave.pVertices[3].c.w -= fAlphaInc;
    }
	else
	{
		m_Status = OG_EFFECTSTATUS_INACTIVE;
	}
}


// Render.
void COGEffectBonusPick::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vWaveUp = m_vCameraUp * m_Wave.scale;
    Vec3 vWaveRight = m_vCameraRight * m_Wave.scale;
    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    m_Wave.pVertices[0].p = vOffset + vWaveRight + vWaveUp;
    m_Wave.pVertices[1].p = vOffset - vWaveRight + vWaveUp;
    m_Wave.pVertices[2].p = vOffset + vWaveRight - vWaveUp;
    m_Wave.pVertices[3].p = vOffset - vWaveRight - vWaveUp;
	m_pRenderer->DrawEffectBuffer(&m_Wave.pVertices[0], 0, 4);
}


// Start.
void COGEffectBonusPick::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEffectBonusPick::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
