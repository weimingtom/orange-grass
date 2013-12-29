/*
 *  ogemittertrail.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemittertrail.h"
#include "OrangeGrass.h"


std::string COGEmitterTrail::s_Alias = std::string("trail");
OGEmitterType COGEmitterTrail::s_Type = OG_EMITTER_TRAIL;


COGEmitterTrail::COGEmitterTrail()
{
    m_fDistanceAccum = 0.0f;
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 5;
    m_fEmitDistance = 0.3f;
    m_fAlphaFade = 0.01f;
    m_fInitialScale = 2.0f;
    m_fScaleInc = 0.1f;
    m_fRotateInc = 0.1f;
    m_color = OGVec4(0.6f, 0.6f, 0.6f, 0.2f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddFloatParam("emit_distance", &m_fEmitDistance);
    AddFloatParam("alpha_fade", &m_fAlphaFade);
    AddFloatParam("scale_inc", &m_fScaleInc);
    AddFloatParam("rotate_inc", &m_fRotateInc);
    AddFloatParam("init_scale", &m_fInitialScale);
    AddColorParam("color", &m_color);
}


COGEmitterTrail::~COGEmitterTrail()
{
    OG_SAFE_DELETE(m_pVBO);
}


// Initialize emitter.
void COGEmitterTrail::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHABLEND;
    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2*60);

    m_bPositionUpdated = false;
    m_BBList.reserve(60);
}


// Update.
void COGEmitterTrail::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    if (iter != m_BBList.end())
    {
        while (iter != m_BBList.end())
        {
            ParticleFormat& particle = (*iter);
            BBVert* pV = (*particle.verts);
            if (pV[0].c.w >= m_fAlphaFade)
            {
                particle.scale += m_fScaleInc;
                particle.angle += m_fRotateInc;
                pV[0].c.w -= m_fAlphaFade;
                pV[1].c.w -= m_fAlphaFade;
                pV[2].c.w -= m_fAlphaFade;
                pV[3].c.w -= m_fAlphaFade;
                ++iter;
            }
            else
            {
                GetEffectsManager()->ReleaseParticle(particle.verts);
                iter = m_BBList.erase(iter);
                if (m_BBList.empty() && m_Status == OG_EFFECTSTATUS_STOPPED)
                {
                    m_Status = OG_EFFECTSTATUS_INACTIVE;
                    return;
                }
            }
        }
    }
    else
    {
        if (m_Status == OG_EFFECTSTATUS_STOPPED)
        {
            m_Status = OG_EFFECTSTATUS_INACTIVE;
            return;
        }
    }

    if (m_Status == OG_EFFECTSTATUS_STARTED && m_bPositionUpdated && m_vCurPosition != m_vPrevPosition)
    {
        OGVec3 vDir = m_vPrevPosition - m_vCurPosition;
        float fDist = vDir.length();
        vDir.normalize();
        unsigned int numVertsAtOnce = (unsigned int)((fDist + m_fDistanceAccum) / m_fEmitDistance);
        if (numVertsAtOnce == 0)
        {
            m_fDistanceAccum += fDist;
        }
        else
        {
            m_fDistanceAccum = 0.0f;
        }

        for (unsigned int n = 0; n < numVertsAtOnce; ++n)
        {
            ParticleFormat particle;
            particle.verts = GetEffectsManager()->AddParticle();
            BBVert* pV = (*particle.verts);
            particle.offset = vDir * (m_fEmitDistance * (float)n);
            particle.scale = m_fInitialScale;
            particle.angle = rand() * 0.01f;
            particle.bDirty = true;
            pV[0].c = m_color;
            pV[1].c = m_color;
            pV[2].c = m_color;
            pV[3].c = m_color;
            m_BBList.push_back(particle);
        }
    }
}


// Render.
void COGEmitterTrail::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGMatrix mR;
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();

    unsigned int vertOffset = 0;
    m_pVBO->Map();

    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);
        if (particle.bDirty)
        {
            particle.offset += m_vCurPosition;
            particle.bDirty = false;
        }

        MatrixRotationAxis(mR, particle.angle, _vLook.x, _vLook.y, _vLook.z);

        OGVec3 vSUp = _vUp * particle.scale;
        OGVec3 vSRight = _vRight * particle.scale;

        BBVert* pVert = (*particle.verts);
        MatrixVecMultiply(pVert[0].p, vSRight + vSUp, mR);
        pVert[0].p += particle.offset;
        pVert[0].t.x = m_pMapping->t1.x; pVert[0].t.y = m_pMapping->t0.y;

        MatrixVecMultiply(pVert[1].p, -vSRight + vSUp, mR);
        pVert[1].p += particle.offset;
        pVert[1].t.x = m_pMapping->t0.x; pVert[1].t.y = m_pMapping->t0.y;

        MatrixVecMultiply(pVert[2].p, vSRight - vSUp, mR);
        pVert[2].p += particle.offset;
        pVert[2].t.x = m_pMapping->t1.x; pVert[2].t.y = m_pMapping->t1.y;

        MatrixVecMultiply(pVert[3].p, -vSRight - vSUp, mR);
        pVert[3].p += particle.offset;
        pVert[3].t.x = m_pMapping->t0.x; pVert[3].t.y = m_pMapping->t1.y;

        m_pVBO->Update(vertOffset, pVert, 4*sizeof(BBVert));
        vertOffset += 4*sizeof(BBVert);
    }
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
}


// Start.
void COGEmitterTrail::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;
    for(auto it = m_BBList.begin(); it != m_BBList.end(); ++it)
    {
        GetEffectsManager()->ReleaseParticle(it->verts);
    }
    m_BBList.clear();
    m_fDistanceAccum = 0.0f;
    m_bPositionUpdated = false;
}


// Stop.
void COGEmitterTrail::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    for(auto it = m_BBList.begin(); it != m_BBList.end(); ++it)
    {
        GetEffectsManager()->ReleaseParticle(it->verts);
    }
    m_BBList.clear();
    m_fDistanceAccum = 0.0f;
    m_Status = OG_EFFECTSTATUS_STOPPED;
    m_bPositionUpdated = false;
}
