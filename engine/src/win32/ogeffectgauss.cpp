/*
 *  ogeffectgauss.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectgauss.h"
#include "OrangeGrass.h"


std::string COGEffectGauss::m_Texture = std::string("effects");
unsigned int COGEffectGauss::m_MappingStartId = 13;
unsigned int COGEffectGauss::m_MappingFinishId = 14;


COGEffectGauss::~COGEffectGauss()
{
}


// Initialize effect.
void COGEffectGauss::Init(OGEffectType _Type)
{
    m_bPosReady = false;
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }
    m_BBList.reserve(16);

	m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectGauss::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    for (unsigned int n = 0; n < 16; ++n)
    {
        if (m_BBList.size() < 16)
        {
            ParticleFormat particle;
            particle.offset = Vec3(0,0,0);
            particle.scale = 1.0f;
            particle.frame = 0.0f;
            particle.angle = 0.0f;
            particle.pVertices[0].c = m_color;
            particle.pVertices[1].c = m_color;
            particle.pVertices[2].c = m_color;
            particle.pVertices[3].c = m_color;
            m_BBList.push_back(particle);
        }
        else
            break;
    }
}


// Render.
void COGEffectGauss::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);

        Vec3 vSUp = Vec3(0,0,-1) * particle.scale;
		Vec3 vSRight = Vec3(1,0,0) * particle.scale;

		particle.pVertices[0].p = particle.offset + vSRight + vSUp + vOffset;
		particle.pVertices[1].p = particle.offset - vSRight + vSUp + vOffset;
		particle.pVertices[2].p = particle.offset + vSRight - vSUp + vOffset;
		particle.pVertices[3].p = particle.offset - vSRight - vSUp + vOffset;

		IOGMapping* pMapping = m_Frames[(unsigned int)particle.frame];
        particle.pVertices[0].t = Vec2(pMapping->t1.x, pMapping->t0.y);
        particle.pVertices[1].t = Vec2(pMapping->t0.x, pMapping->t0.y);
        particle.pVertices[2].t = Vec2(pMapping->t1.x, pMapping->t1.y);
        particle.pVertices[3].t = Vec2(pMapping->t0.x, pMapping->t1.y);

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }
}


// Start.
void COGEffectGauss::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BBList.clear();
}


// Stop.
void COGEffectGauss::Stop ()
{
    m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BBList.clear();
    m_bPosReady = false;
}


// Set start and finish positions.
void COGEffectGauss::SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos)
{
    m_bPosReady = true;
    m_vStartPos = _vStartPos;
    m_vFinishPos = _vFinishPos;
}
