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


std::string COGEmitterPulseGlow::s_Alias = std::string("pulse_glow");
OGEmitterType COGEmitterPulseGlow::s_Type = OG_EMITTER_PULSEGLOW;


COGEmitterPulseGlow::COGEmitterPulseGlow()
{
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 8;
    m_fInitialScale = 16.0f;
    m_fGlowAlphaInc = 0.08f;
    m_fAlphaInc = 0.02f;
    m_color = OGVec4(1.0f, 1.0f, 1.0f, 0.4f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddFloatParam("init_scale", &m_fInitialScale);
    AddFloatParam("glow_alpha_inc", &m_fGlowAlphaInc);
    AddFloatParam("alpha_inc", &m_fAlphaInc);
    AddColorParam("color", &m_color);
}


COGEmitterPulseGlow::~COGEmitterPulseGlow()
{
    OG_SAFE_DELETE(m_pVBO);
    GetEffectsManager()->ReleaseParticle(m_Glow.verts);
}


// Initialize emitter.
void COGEmitterPulseGlow::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2);
    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAONE;

    m_Glow.scale = m_fInitialScale;
    m_Glow.verts = GetEffectsManager()->AddParticle();
    BBVert* pV = (*m_Glow.verts);
    pV[0].c = m_color;
    pV[0].t = OGVec2(m_pMapping->t1.x, m_pMapping->t0.y);
    pV[1].c = m_color;
    pV[1].t = OGVec2(m_pMapping->t0.x, m_pMapping->t0.y);
    pV[2].c = m_color;
    pV[2].t = OGVec2(m_pMapping->t1.x, m_pMapping->t1.y);
    pV[3].c = m_color;
    pV[3].t = OGVec2(m_pMapping->t0.x, m_pMapping->t1.y);

    m_bPositionUpdated = false;
}


// Update.
void COGEmitterPulseGlow::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    BBVert* pV = (*m_Glow.verts);

    switch (m_Status)
    {
    case OG_EFFECTSTATUS_STARTED:
        {
            if (m_GlowPulse == 1)
            {
                if (pV[0].c.w >= m_fAlphaInc)
                {
                    pV[0].c.w -= m_fAlphaInc;
                    pV[1].c.w -= m_fAlphaInc;
                    pV[2].c.w -= m_fAlphaInc;
                    pV[3].c.w -= m_fAlphaInc;
                }
                else
                {
                    m_GlowPulse = -1;
                }
            }
            else
            {
                if (pV[0].c.w < 0.4f - m_fAlphaInc)
                {
                    pV[0].c.w += m_fAlphaInc;
                    pV[1].c.w += m_fAlphaInc;
                    pV[2].c.w += m_fAlphaInc;
                    pV[3].c.w += m_fAlphaInc;
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
            if (pV[0].c.w >= m_fGlowAlphaInc)
            {
                m_Glow.scale += 2.0f;
                pV[0].c.w -= m_fGlowAlphaInc;
                pV[1].c.w -= m_fGlowAlphaInc;
                pV[2].c.w -= m_fGlowAlphaInc;
                pV[3].c.w -= m_fGlowAlphaInc;
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
void COGEmitterPulseGlow::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGVec3 vOffset = OGVec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    OGVec3 vGlowUp = _vUp * m_Glow.scale;
    OGVec3 vGlowRight = _vRight * m_Glow.scale;
    BBVert* pV = (*m_Glow.verts);
    pV[0].p = vOffset + vGlowRight + vGlowUp;
    pV[1].p = vOffset - vGlowRight + vGlowUp;
    pV[2].p = vOffset + vGlowRight - vGlowUp;
    pV[3].p = vOffset - vGlowRight - vGlowUp;

    m_pVBO->Map();
    m_pVBO->Update(0, pV, 4*sizeof(BBVert));
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
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
    BBVert* pV = (*m_Glow.verts);
    pV[0].c.w = 1.0f;
    pV[1].c.w = 1.0f;
    pV[2].c.w = 1.0f;
    pV[3].c.w = 1.0f;
}
