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


float COGEffectBonusPick::m_fAlphaInc;
float COGEffectBonusPick::m_fScaleInc;
float COGEffectBonusPick::m_fInitialScale;
std::string COGEffectBonusPick::m_Texture;
unsigned int COGEffectBonusPick::m_MappingId;

float COGEffectBonusPick::m_fGlowAlphaInc = 0.08f;


COGEffectBonusPick::~COGEffectBonusPick()
{
}


// Load params.
bool COGEffectBonusPick::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/bonuspick.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fAlphaInc = pReader->ReadFloatParam(pRoot, "alpha_inc");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectBonusPick::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_Blend = OG_BLEND_ALPHABLEND;

    Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 0.5f);
    m_pWaveMapping = m_pTexture->GetMapping(m_MappingId);
    m_pGlowMapping = m_pTexture->GetMapping(8);
    int a = 0;
    for (int i = 0; i < MAXPART; ++i)
    {
        ParticleFormat& p = m_BB[i];
        p.scale = m_fInitialScale;
        p.angle = 0.0f;
        p.axis = a;
        p.tilt = i * 0.7f;
        p.offset = Vec3(0,0,0);
        color.y = GetRandomRange(0, 90) * 0.01f;
        color.z = GetRandomRange(0, 70) * 0.01f;
        p.pVertices[0].c = color;
        p.pVertices[0].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t0.y);
        p.pVertices[1].c = color;
        p.pVertices[1].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t0.y);
        p.pVertices[2].c = color;
        p.pVertices[2].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t1.y);
        p.pVertices[3].c = color;
        p.pVertices[3].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t1.y);
        p.bDirty = true;
        ++a;
        if (a > 2)
            a = 0;
    }

    Vec4 glow_color = Vec4(1.0f, 1.0f, 1.0f, 0.4f);
    m_Glow.scale = 16.0f;
    m_Glow.angle = 0.0f;
    m_Glow.pVertices[0].c = glow_color;
    m_Glow.pVertices[0].t = Vec2(m_pGlowMapping->t1.x, m_pGlowMapping->t0.y);
    m_Glow.pVertices[1].c = glow_color;
    m_Glow.pVertices[1].t = Vec2(m_pGlowMapping->t0.x, m_pGlowMapping->t0.y);
    m_Glow.pVertices[2].c = glow_color;
    m_Glow.pVertices[2].t = Vec2(m_pGlowMapping->t1.x, m_pGlowMapping->t1.y);
    m_Glow.pVertices[3].c = glow_color;
    m_Glow.pVertices[3].t = Vec2(m_pGlowMapping->t0.x, m_pGlowMapping->t1.y);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectBonusPick::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    switch (m_Status)
    {
    case OG_EFFECTSTATUS_STARTED:
        {
            for (int i = 0; i < MAXPART; ++i)
            {
                ParticleFormat& p = m_BB[i];
                p.angle += 0.1f;
            }
            
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
                m_Glow.scale += 2.0f;//m_fScaleInc;
                m_Glow.pVertices[0].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[1].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[2].c.w -= m_fGlowAlphaInc;
                m_Glow.pVertices[3].c.w -= m_fGlowAlphaInc;
            }
            else
            {
                //m_Status = OG_EFFECTSTATUS_INACTIVE;
                //return;
            }

            for (int i = 0; i < MAXPART; ++i)
            {
                ParticleFormat& p = m_BB[i];
                if (p.pVertices[0].c.w >= m_fAlphaInc)
                {
                    //p.scale += m_fScaleInc;
                    p.angle += 0.1f;
                    p.pVertices[0].c.w -= m_fAlphaInc;
                    p.pVertices[1].c.w -= m_fAlphaInc;
                    p.pVertices[2].c.w -= m_fAlphaInc;
                    p.pVertices[3].c.w -= m_fAlphaInc;
                }
                else
                {
                    m_Status = OG_EFFECTSTATUS_INACTIVE;
                    return;
                }
            }
        }
        break;

    case OG_EFFECTSTATUS_INACTIVE:
    default:
        return;
    }
}


// Render.
void COGEffectBonusPick::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    MATRIX mR;
    for (int i = 0; i < MAXPART; ++i)
    {
        ParticleFormat& p = m_BB[i];

        Vec3 vWaveUp = m_vCameraUp * p.scale;
        Vec3 vWaveRight = m_vCameraRight * p.scale;

        if (m_Status == OG_EFFECTSTATUS_STARTED)
        {
            if (p.axis == 0)
                MatrixRotationX(mR, p.tilt);
            else if (p.axis == 1)
                MatrixRotationY(mR, p.tilt);
            else
                MatrixRotationZ(mR, p.tilt);
            p.offset = Vec3(10, 0, 0);
            if (p.bDirty)
            {
                p.bDirty = false;
            }
            Rotate2DPoint(p.offset.x, p.offset.z, p.angle, 0, 0);
            MatrixVec3Multiply(p.offset, p.offset, mR);
        }
        else if (m_Status == OG_EFFECTSTATUS_STOPPED)
        {
            Vec3 vDir = (p.pVertices[0].p - vOffset).normalized();
            p.offset += vDir * 3;
        }

        p.pVertices[0].p = vOffset + p.offset + vWaveRight + vWaveUp;
        p.pVertices[1].p = vOffset + p.offset - vWaveRight + vWaveUp;
        p.pVertices[2].p = vOffset + p.offset + vWaveRight - vWaveUp;
        p.pVertices[3].p = vOffset + p.offset - vWaveRight - vWaveUp;
        m_pRenderer->DrawEffectBuffer(&p.pVertices[0], 0, 4);
    }

    Vec3 vGlowUp = m_vCameraUp * m_Glow.scale;
    Vec3 vGlowRight = m_vCameraRight * m_Glow.scale;
    m_Glow.pVertices[0].p = vOffset + vGlowRight + vGlowUp;
    m_Glow.pVertices[1].p = vOffset - vGlowRight + vGlowUp;
    m_Glow.pVertices[2].p = vOffset + vGlowRight - vGlowUp;
    m_Glow.pVertices[3].p = vOffset - vGlowRight - vGlowUp;
    m_pRenderer->DrawEffectBuffer(&m_Glow.pVertices[0], 0, 4);
}


// Start.
void COGEffectBonusPick::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_GlowPulse = 1;
}


// Stop.
void COGEffectBonusPick::Stop ()
{
	m_Status = OG_EFFECTSTATUS_STOPPED;
    m_Glow.pVertices[0].c.w = 1.0f;
    m_Glow.pVertices[1].c.w = 1.0f;
    m_Glow.pVertices[2].c.w = 1.0f;
    m_Glow.pVertices[3].c.w = 1.0f;
}
