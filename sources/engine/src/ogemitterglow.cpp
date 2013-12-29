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
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 9;
    m_fInitialScale = 2.0f;
    m_fInitialAngleMin = -3.14f;
    m_fInitialAngleMax = 3.14f;
    m_color = OGVec4(1.0f, 1.0f, 1.0f, 0.6f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddFloatParam("init_angle_min", &m_fInitialAngleMin);
    AddFloatParam("init_angle_max", &m_fInitialAngleMax);
    AddFloatParam("init_scale", &m_fInitialScale);
    AddColorParam("color", &m_color);
}


COGEmitterGlow::~COGEmitterGlow()
{
    OG_SAFE_DELETE(m_pVBO);
    GetEffectsManager()->ReleaseParticle(m_Glow.verts);
}


// Initialize emitter.
void COGEmitterGlow::Init (IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAONE;
    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2);

    m_Glow.scale = m_fInitialScale;
    m_Glow.angle = GetRandomRange(
        (int)(m_fInitialAngleMin * 100.0f), 
        (int)(m_fInitialAngleMax * 100.0f)) * 0.01f;
    m_Glow.verts = GetEffectsManager()->AddParticle();
    BBVert* pV = (*m_Glow.verts);
    pV[0].c = m_color;
    pV[1].c = m_color;
    pV[2].c = m_color;
    pV[3].c = m_color;

    m_bPositionUpdated = false;
}


// Update.
void COGEmitterGlow::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;
}


// Render.
void COGEmitterGlow::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    if (m_Status != OG_EFFECTSTATUS_STOPPED)
    {
        OGMatrix mR;
        MatrixRotationAxis(mR, m_Glow.angle, _vLook.x, _vLook.y, _vLook.z);

        OGVec3 vSUp = _vUp * m_Glow.scale;
        OGVec3 vSRight = _vRight * m_Glow.scale;

        BBVert* pVert = (*m_Glow.verts);
        MatrixVecMultiply(pVert[0].p, vSRight + vSUp, mR);
        pVert[0].p += m_vCurPosition;
        pVert[0].t.x = m_pMapping->t1.x; pVert[0].t.y = m_pMapping->t0.y;

        MatrixVecMultiply(pVert[1].p, -vSRight + vSUp, mR);
        pVert[1].p += m_vCurPosition;
        pVert[1].t.x = m_pMapping->t0.x; pVert[1].t.y = m_pMapping->t0.y;

        MatrixVecMultiply(pVert[2].p, vSRight - vSUp, mR);
        pVert[2].p += m_vCurPosition;
        pVert[2].t.x = m_pMapping->t1.x; pVert[2].t.y = m_pMapping->t1.y;

        MatrixVecMultiply(pVert[3].p, -vSRight - vSUp, mR);
        pVert[3].p += m_vCurPosition;
        pVert[3].t.x = m_pMapping->t0.x; pVert[3].t.y = m_pMapping->t1.y;

        m_pVBO->Map();
        m_pVBO->Update(0, pVert, 4*sizeof(BBVert));
        m_pVBO->Unmap();
        m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
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
