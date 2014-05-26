/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "ogemitterparticlechain.h"
#include "OrangeGrass.h"


std::string COGEmitterParticleChain::s_Alias = std::string("particle_chain");
OGEmitterType COGEmitterParticleChain::s_Type = OG_EMITTER_PARTICLECHAIN;


COGEmitterParticleChain::COGEmitterParticleChain()
{
    m_pVBO = NULL;

    m_Texture = std::string("effects");
    m_MappingId = 12;
    m_NumParticles = 12;
    m_color = OGVec4(0.6f, 0.7f, 1.0f, 0.2f);

    AddStringParam("texture", &m_Texture);
    AddIntParam("mapping", &m_MappingId);
    AddIntParam("num_particles", &m_NumParticles);
    AddColorParam("color", &m_color);
}


COGEmitterParticleChain::~COGEmitterParticleChain()
{
    OG_SAFE_DELETE(m_pVBO);
    for(auto it = m_BBList.begin(); it != m_BBList.end(); ++it)
    {
        GetEffectsManager()->ReleaseParticle(it->verts);
    }
    m_BBList.clear();
}


// Initialize emitter.
void COGEmitterParticleChain::Init(IOGGroupNode* _pNode)
{
    LoadParams(_pNode);

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Texture);
    m_Blend = OG_BLEND_ALPHAONE;
    m_pMapping = m_pTexture->GetMapping(m_MappingId);

    m_BBList.reserve(m_NumParticles);
    m_pVBO = m_pRenderer->CreateDynVertexBuffer(2*m_NumParticles);

    for (unsigned int i = 0; i < m_NumParticles; ++i)
    {
        ParticleFormat particle;
        particle.scale = ((float)m_NumParticles - i) / 6.5f;
        particle.verts = GetEffectsManager()->AddParticle();
        BBVert* pV = (*particle.verts);
        pV[0].t = OGVec2(m_pMapping->t1.x, m_pMapping->t0.y);
        pV[1].t = OGVec2(m_pMapping->t0.x, m_pMapping->t0.y);
        pV[2].t = OGVec2(m_pMapping->t1.x, m_pMapping->t1.y);
        pV[3].t = OGVec2(m_pMapping->t0.x, m_pMapping->t1.y);
        pV[0].c = m_color;
        pV[1].c = m_color;
        pV[2].c = m_color;
        pV[3].c = m_color;
        m_BBList.push_back(particle);
    }

    m_bPositionUpdated = false;
}


// Update.
void COGEmitterParticleChain::Update (unsigned long _ElapsedTime)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    for (unsigned int i = 0; i < m_NumParticles; ++i)
    {
        m_BBList[i].offset = m_Direction * (float)i;
    }
}


// Render.
void COGEmitterParticleChain::Render (const OGMatrix& _mWorld, const OGVec3& _vLook, const OGVec3& _vUp, const OGVec3& _vRight, OGRenderPass _Pass)
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    OGVec3 vOffset = OGVec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);

    unsigned int vertOffset = 0;
    m_pVBO->Map();

    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = *iter;
        OGVec3 vSUp = _vUp * particle.scale;
        OGVec3 vSRight = _vRight * particle.scale;
        BBVert* pV = (*particle.verts);
        pV[0].p = vOffset + vSRight + vSUp + particle.offset;
        pV[1].p = vOffset - vSRight + vSUp + particle.offset;
        pV[2].p = vOffset + vSRight - vSUp + particle.offset;
        pV[3].p = vOffset - vSRight - vSUp + particle.offset;

        m_pVBO->Update(vertOffset, pV, 4*sizeof(BBVert));
        vertOffset += 4*sizeof(BBVert);
    }
    m_pVBO->Unmap();
    m_pRenderer->RenderEffect(m_pTexture, m_pVBO, m_Blend, OG_SHADER_COLOREFFECT, _Pass);
}


// Start.
void COGEmitterParticleChain::Start ()
{
    m_Status = OG_EFFECTSTATUS_STARTED;
    Update(0);
}


// Stop.
void COGEmitterParticleChain::Stop ()
{
    if (m_Status == OG_EFFECTSTATUS_INACTIVE)
        return;

    m_Status = OG_EFFECTSTATUS_INACTIVE;
}
