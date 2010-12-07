/*
 *  ogemitterringwave.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterringwave.h"
#include "OrangeGrass.h"


COGEmitterRingWave::COGEmitterRingWave()
{
	m_Texture = std::string("effects");
	m_MappingId = 10;
	m_fInitialScale = 8.0f;
	m_fScaleInc = 1.5f;
	m_fAlphaDec = 0.08f;
	m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

	AddStringParam("texture", &m_Texture);
	AddIntParam("mapping", &m_MappingId);
	AddFloatParam("init_scale", &m_fInitialScale);
	AddFloatParam("scale_inc", &m_fScaleInc);
	AddFloatParam("alpha_dec", &m_fAlphaDec);
	AddColorParam("color", &m_color);
}


COGEmitterRingWave::~COGEmitterRingWave()
{
}


// Initialize emitter.
void COGEmitterRingWave::Init(IOGGroupNode* _pNode)
{
	LoadParams(_pNode);

	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHABLEND;

    m_Wave.pVertices[0].t = Vec2(m_pMapping->t1.x, m_pMapping->t0.y);
    m_Wave.pVertices[1].t = Vec2(m_pMapping->t0.x, m_pMapping->t0.y);
    m_Wave.pVertices[2].t = Vec2(m_pMapping->t1.x, m_pMapping->t1.y);
    m_Wave.pVertices[3].t = Vec2(m_pMapping->t0.x, m_pMapping->t1.y);

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterRingWave::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (m_Wave.pVertices[0].c.w >= m_fAlphaDec)
    {
        m_Wave.scale += m_fScaleInc;
        m_Wave.pVertices[0].c.w -= m_fAlphaDec;
        m_Wave.pVertices[1].c.w -= m_fAlphaDec;
        m_Wave.pVertices[2].c.w -= m_fAlphaDec;
        m_Wave.pVertices[3].c.w -= m_fAlphaDec;
    }
}


// Render.
void COGEmitterRingWave::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    Vec3 vUp = Vec3(0,0,1) * m_Wave.scale;
    Vec3 vRight = Vec3(1,0,0) * m_Wave.scale;
    m_Wave.pVertices[0].p = vOffset + vRight + vUp;
    m_Wave.pVertices[1].p = vOffset - vRight + vUp;
    m_Wave.pVertices[2].p = vOffset + vRight - vUp;
    m_Wave.pVertices[3].p = vOffset - vRight - vUp;
	m_pRenderer->DrawEffectBuffer(&m_Wave.pVertices[0], 0, 4);
}


// Start.
void COGEmitterRingWave::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

    m_Wave.scale = m_fInitialScale;
    m_Wave.pVertices[0].c = m_color;
    m_Wave.pVertices[1].c = m_color;
    m_Wave.pVertices[2].c = m_color;
    m_Wave.pVertices[3].c = m_color;
}


// Stop.
void COGEmitterRingWave::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
