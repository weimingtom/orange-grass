/*
 *  ogemitterrotatingsparks.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitterrotatingsparks.h"
#include "OrangeGrass.h"


std::string COGEmitterRotatingSparks::s_Alias = std::string("rotating_sparks");
OGEmitterType COGEmitterRotatingSparks::s_Type = OG_EMITTER_ROTATINGSPARKS;


COGEmitterRotatingSparks::COGEmitterRotatingSparks()
{
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 11;
    m_NumParticles = 10;
    m_fAlphaInc = 0.02f;
    m_fScaleInc = 1.5f;
    m_fInitialScale = 3.0f;
    m_color = OGVec4(1.0f, 1.0f, 1.0f, 0.5f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddIntParam("num_particles", &m_NumParticles);
    AddFloatParam("alpha_inc", &m_fAlphaInc);
    AddFloatParam("scale_inc", &m_fScaleInc);
    AddFloatParam("init_scale", &m_fInitialScale);
    AddColorParam("color", &m_color);
}


COGEmitterRotatingSparks::~COGEmitterRotatingSparks()
{
    OG_SAFE_DELETE(m_pVBO);
    for(auto it = m_BBList.begin(); it != m_BBList.end(); ++it)
    {
        GetEffectsManager()->ReleaseParticle(it->verts);
    }
}


// Initialize emitter.
void COGEmitterRotatingSparks::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHAONE;

    m_BBList.reserve(m_NumParticles);
    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2*m_NumParticles);

    int a = 0;
    for (unsigned int i = 0; i < m_NumParticles; ++i)
    {
        ParticleFormat p;
        p.scale = m_fInitialScale;
        p.angle = 0.0f;
        p.axis = a;
        p.tilt = i * 0.7f;
        p.offset = OGVec3(0,0,0);
        m_color.y = GetRandomRange(0, 90) * 0.01f;
        m_color.z = GetRandomRange(0, 70) * 0.01f;
        p.verts = GetEffectsManager()->AddParticle();
        BBVert* pV = (*p.verts);
        pV[0].c = m_color;
        pV[0].t = OGVec2(m_pMapping->t1.x, m_pMapping->t0.y);
        pV[1].c = m_color;
        pV[1].t = OGVec2(m_pMapping->t0.x, m_pMapping->t0.y);
        pV[2].c = m_color;
        pV[2].t = OGVec2(m_pMapping->t1.x, m_pMapping->t1.y);
        pV[3].c = m_color;
        pV[3].t = OGVec2(m_pMapping->t0.x, m_pMapping->t1.y);
        p.bDirty = true;
        ++a;
        if (a > 2)
            a = 0;
        m_BBList.push_back(p);
    }

    m_bPositionUpdated = false;
}


// Update.
void COGEmitterRotatingSparks::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    switch (m_Status)
    {
    case OG_EFFECTSTATUS_STARTED:
        {
            std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
            for (; iter != m_BBList.end(); ++iter)
            {
                ParticleFormat& p = (*iter);
                p.angle += 0.1f;
            }
        }
        break;

    case OG_EFFECTSTATUS_STOPPED:
        {
            std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
            for (; iter != m_BBList.end(); ++iter)
            {
                ParticleFormat& p = (*iter);
                BBVert* pV = (*p.verts);
                if (pV[0].c.w >= m_fAlphaInc)
                {
                    p.angle += 0.1f;
                    pV[0].c.w -= m_fAlphaInc;
                    pV[1].c.w -= m_fAlphaInc;
                    pV[2].c.w -= m_fAlphaInc;
                    pV[3].c.w -= m_fAlphaInc;
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
void COGEmitterRotatingSparks::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGVec3 vOffset = OGVec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    unsigned int vertOffset = 0;
    m_pVBO->Map();

    OGMatrix mR;
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& p = (*iter);

        OGVec3 vUp = _vUp * p.scale;
        OGVec3 vRight = _vRight * p.scale;

        BBVert* pV = (*p.verts);

        if (m_Status == OG_EFFECTSTATUS_STARTED)
        {
            if (p.axis == 0)
                MatrixRotationX(mR, p.tilt);
            else if (p.axis == 1)
                MatrixRotationY(mR, p.tilt);
            else
                MatrixRotationZ(mR, p.tilt);
            p.offset = OGVec3(10, 0, 0);
            if (p.bDirty)
            {
                p.bDirty = false;
            }
            Rotate2DPoint(p.offset.x, p.offset.z, p.angle, 0, 0);
            MatrixVec3Multiply(p.offset, p.offset, mR);
        }
        else if (m_Status == OG_EFFECTSTATUS_STOPPED)
        {
            OGVec3 vDir = (pV[0].p - vOffset).normalized();
            p.offset += vDir * 3;
        }

        pV[0].p = vOffset + p.offset + vRight + vUp;
        pV[1].p = vOffset + p.offset - vRight + vUp;
        pV[2].p = vOffset + p.offset + vRight - vUp;
        pV[3].p = vOffset + p.offset - vRight - vUp;
        m_pVBO->Update(vertOffset, pV, 4*sizeof(BBVert));
        vertOffset += 4*sizeof(BBVert);
    }
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
}


// Start.
void COGEmitterRotatingSparks::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;
}


// Stop.
void COGEmitterRotatingSparks::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    m_Status = OG_EFFECTSTATUS_STOPPED;
}
