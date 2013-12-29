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


std::string COGEmitterRingWave::s_Alias = std::string("ring_wave");
OGEmitterType COGEmitterRingWave::s_Type = OG_EMITTER_RINGWAVE;


COGEmitterRingWave::COGEmitterRingWave()
{
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 10;
    m_fInitialScale = 8.0f;
    m_fScaleInc = 1.5f;
    m_fAlphaDec = 0.08f;
    m_color = OGVec4(1.0f, 1.0f, 1.0f, 1.0f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddFloatParam("init_scale", &m_fInitialScale);
    AddFloatParam("scale_inc", &m_fScaleInc);
    AddFloatParam("alpha_dec", &m_fAlphaDec);
    AddColorParam("color", &m_color);
}


COGEmitterRingWave::~COGEmitterRingWave()
{
    OG_SAFE_DELETE(m_pVBO);
    GetEffectsManager()->ReleaseParticle(m_Wave.verts);
}


// Initialize emitter.
void COGEmitterRingWave::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2);
    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAONE;

    m_Wave.verts = GetEffectsManager()->AddParticle();
    BBVert* pV = (*m_Wave.verts);
    pV[0].t = OGVec2(m_pMapping->t1.x, m_pMapping->t0.y);
    pV[1].t = OGVec2(m_pMapping->t0.x, m_pMapping->t0.y);
    pV[2].t = OGVec2(m_pMapping->t1.x, m_pMapping->t1.y);
    pV[3].t = OGVec2(m_pMapping->t0.x, m_pMapping->t1.y);

    m_bPositionUpdated = false;
}


// Update.
void COGEmitterRingWave::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    BBVert* pV = (*m_Wave.verts);
    if (pV[0].c.w >= m_fAlphaDec)
    {
        m_Wave.scale += m_fScaleInc;
        pV[0].c.w -= m_fAlphaDec;
        pV[1].c.w -= m_fAlphaDec;
        pV[2].c.w -= m_fAlphaDec;
        pV[3].c.w -= m_fAlphaDec;
    }
    else
    {
        Stop();
        return;
    }
}


// Render.
void COGEmitterRingWave::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGVec3 vOffset = OGVec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    OGVec3 vUp = OGVec3(0,0,1) * m_Wave.scale;
    OGVec3 vRight = OGVec3(1,0,0) * m_Wave.scale;
    BBVert* pV = (*m_Wave.verts);
    pV[0].p = vOffset + vRight + vUp;
    pV[1].p = vOffset - vRight + vUp;
    pV[2].p = vOffset + vRight - vUp;
    pV[3].p = vOffset - vRight - vUp;
    m_pVBO->Map();
    m_pVBO->Update(0, pV, 4*sizeof(BBVert));
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
}


// Start.
void COGEmitterRingWave::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;

    m_Wave.scale = m_fInitialScale;
    BBVert* pV = (*m_Wave.verts);
    pV[0].c = m_color;
    pV[1].c = m_color;
    pV[2].c = m_color;
    pV[3].c = m_color;
}


// Stop.
void COGEmitterRingWave::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    m_Status = OG_EFFECTSTATUS_INACTIVE;
}
