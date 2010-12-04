/*
 *  ogemitterpulseglow.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterpulseglow.h"
#include "OrangeGrass.h"


COGEmitterPulseGlow::COGEmitterPulseGlow()
{
}


COGEmitterPulseGlow::~COGEmitterPulseGlow()
{
}


// Initialize emitter.
void COGEmitterPulseGlow::Init(IOGGroupNode* _pNode)
{
	m_MappingId = 8;
    m_color = Vec4(1.0f, 1.0f, 1.0f, 0.4f);

	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHABLEND;

    m_Glow.scale = 16.0f;
    m_Glow.pVertices[0].c = m_color;
    m_Glow.pVertices[0].t = Vec2(m_pMapping->t1.x, m_pMapping->t0.y);
    m_Glow.pVertices[1].c = m_color;
    m_Glow.pVertices[1].t = Vec2(m_pMapping->t0.x, m_pMapping->t0.y);
    m_Glow.pVertices[2].c = m_color;
    m_Glow.pVertices[2].t = Vec2(m_pMapping->t1.x, m_pMapping->t1.y);
    m_Glow.pVertices[3].c = m_color;
    m_Glow.pVertices[3].t = Vec2(m_pMapping->t0.x, m_pMapping->t1.y);

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterPulseGlow::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    switch (m_Status)
    {
    case OG_EFFECTSTATUS_STARTED:
        {
            if (m_GlowPulse == 1)
            {
                if (m_Glow.pVertices[0].c.w >= m_fAlphaInc)
                {
                    m_Glow.pVertices[0].c.w -= m_fAlphaInc;
                    m_Glow.pVertices[1].c.w -= m_fAlphaInc;
                    m_Glow.pVertices[2].c.w -= m_fAlphaInc;
                    m_Glow.pVertices[3].c.w -= m_fAlphaInc;
                }
                else
                {
                    m_GlowPulse = -1;
                }
            }
            else
            {
                if (m_Glow.pVertices[0].c.w < 0.4f - m_fAlphaInc)
                {
                    m_Glow.pVertices[0].c.w += m_fAlphaInc;
                    m_Glow.pVertices[1].c.w += m_fAlphaInc;
                    m_Glow.pVertices[2].c.w += m_fAlphaInc;
                    m_Glow.pVertices[3].c.w += m_fAlphaInc;
                }
                else
                {
                    m_GlowPulse = 1;
                }
            }
        }
        break;

    case OG_EFFECTSTATUS_STOPPED:
        {
            if (m_Glow.pVertices[0].c.w >= m_fGlowAlphaInc)
            {
                m_Glow.scale += 2.0f;
                m_Glow.pVertices[0].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[1].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[2].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[3].c.w -= m_fGlowAlphaInc;
            }
            else
            {
                m_Status = OG_EFFECTSTATUS_INACTIVE;
            }
        }
        break;

    case OG_EFFECTSTATUS_INACTIVE:
    default:
        return;
    }
}


// Render.
void COGEmitterPulseGlow::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(OG_BLEND_ALPHABLEND);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

	m_pRenderer->SetBlend(m_Blend);
    Vec3 vGlowUp = _vUp * m_Glow.scale;
    Vec3 vGlowRight = _vRight * m_Glow.scale;
    m_Glow.pVertices[0].p = vOffset + vGlowRight + vGlowUp;
    m_Glow.pVertices[1].p = vOffset - vGlowRight + vGlowUp;
    m_Glow.pVertices[2].p = vOffset + vGlowRight - vGlowUp;
    m_Glow.pVertices[3].p = vOffset - vGlowRight - vGlowUp;
    m_pRenderer->DrawEffectBuffer(&m_Glow.pVertices[0], 0, 4);
}


// Start.
void COGEmitterPulseGlow::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_GlowPulse = 1;
}


// Stop.
void COGEmitterPulseGlow::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
    m_Glow.pVertices[0].c.w = 1.0f;
    m_Glow.pVertices[1].c.w = 1.0f;
    m_Glow.pVertices[2].c.w = 1.0f;
    m_Glow.pVertices[3].c.w = 1.0f;
}
