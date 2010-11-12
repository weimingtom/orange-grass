/*
 *  ogeffectexplosion.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectexplosion.h"
#include "OrangeGrass.h"


std::string COGEffectExplosion::m_Texture = std::string("effects");
unsigned int COGEffectExplosion::m_MaxParticles = 6;
unsigned int COGEffectExplosion::m_MappingStartId = 1;
unsigned int COGEffectExplosion::m_MappingFinishId = 7;
float COGEffectExplosion::m_fFrameInc = 0.38f;
float COGEffectExplosion::m_fInitialScale = 8.0f;
float COGEffectExplosion::m_fScaleInc = 0.6f;
unsigned int COGEffectExplosion::m_numVertsAtOnce = 5;
float COGEffectExplosion::m_fRotateInc = 0.1f;
int COGEffectExplosion::m_offset_min = -4;
int	COGEffectExplosion::m_offset_max = 4;

float COGEffectExplosion::m_fWaveInitialScale = 8.0f;
float COGEffectExplosion::m_fWaveAlphaDec = 0.08f;
float COGEffectExplosion::m_fWaveScaleInc = 1.5f;
unsigned int COGEffectExplosion::m_WaveMappingId = 10;


COGEffectExplosion::~COGEffectExplosion()
{
}


// Initialize effect.
void COGEffectExplosion::Init(OGEffectType _Type)
{
    m_pLight = NULL;
	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }
    m_BBList.reserve(m_MaxParticles);

	m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    m_pWaveMapping = m_pTexture->GetMapping(m_WaveMappingId);
    m_Wave.scale = m_fWaveInitialScale;
    m_Wave.frame = 0.0f;
    m_Wave.angle = 0.0f;
    m_Wave.offset = Vec3(0,0,0);
    m_Wave.pVertices[0].c = m_color;
    m_Wave.pVertices[1].c = m_color;
    m_Wave.pVertices[2].c = m_color;
    m_Wave.pVertices[3].c = m_color;
    m_Wave.pVertices[0].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t0.y);
    m_Wave.pVertices[1].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t0.y);
    m_Wave.pVertices[2].t = Vec2(m_pWaveMapping->t1.x, m_pWaveMapping->t1.y);
    m_Wave.pVertices[3].t = Vec2(m_pWaveMapping->t0.x, m_pWaveMapping->t1.y);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectExplosion::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        ParticleFormat& particle = (*iter);
        if (particle.frame < m_Frames.size() - 1)
        {
            particle.scale += m_fScaleInc;
            particle.angle += m_fRotateInc;
            particle.frame += m_fFrameInc;
            ++iter;
        }
        else
        {
            iter = m_BBList.erase(iter);
            if (m_BBList.empty())
            {
                Stop();
                return;
            }
        }
    }

    if (m_Wave.pVertices[0].c.w >= m_fWaveAlphaDec)
    {
        m_Wave.scale += m_fWaveScaleInc;
        m_Wave.pVertices[0].c.w -= m_fWaveAlphaDec;
        m_Wave.pVertices[1].c.w -= m_fWaveAlphaDec;
        m_Wave.pVertices[2].c.w -= m_fWaveAlphaDec;
        m_Wave.pVertices[3].c.w -= m_fWaveAlphaDec;
    }

	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
    for (unsigned int n = 0; n < m_numVertsAtOnce; ++n)
    {
        if (m_BBList.size() < m_MaxParticles-1)
        {
            ParticleFormat particle;
            particle.offset = Vec3(
				(float)GetRandomRange(m_offset_min,m_offset_max),
				(float)GetRandomRange(m_offset_min,m_offset_max),
				(float)GetRandomRange(m_offset_min,m_offset_max));
            particle.scale = m_fInitialScale;
            particle.frame = 0.0f;
            particle.angle = GetRandomRange(-314,314) * 0.01f;
            particle.pVertices[0].c = m_color;
            particle.pVertices[1].c = m_color;
            particle.pVertices[2].c = m_color;
            particle.pVertices[3].c = m_color;
            m_BBList.push_back(particle);
        }
    }
}


// Render.
void COGEffectExplosion::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    MATRIX mR;
    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);

        MatrixRotationAxis(mR, particle.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

        Vec3 vSUp = m_vCameraUp * particle.scale;
		Vec3 vSRight = m_vCameraRight * particle.scale;

        MatrixVecMultiply(particle.pVertices[0].p, vSRight + vSUp, mR);
        MatrixVecMultiply(particle.pVertices[1].p, -vSRight + vSUp, mR);
        MatrixVecMultiply(particle.pVertices[2].p, vSRight - vSUp, mR);
        MatrixVecMultiply(particle.pVertices[3].p, -vSRight - vSUp, mR);

		particle.pVertices[0].p += particle.offset + vOffset;
		particle.pVertices[1].p += particle.offset + vOffset;
		particle.pVertices[2].p += particle.offset + vOffset;
		particle.pVertices[3].p += particle.offset + vOffset;

		IOGMapping* pMapping = m_Frames[(unsigned int)particle.frame];
        particle.pVertices[0].t = Vec2(pMapping->t1.x, pMapping->t0.y);
        particle.pVertices[1].t = Vec2(pMapping->t0.x, pMapping->t0.y);
        particle.pVertices[2].t = Vec2(pMapping->t1.x, pMapping->t1.y);
        particle.pVertices[3].t = Vec2(pMapping->t0.x, pMapping->t1.y);

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }

    Vec3 vWaveUp = Vec3(0,0,1) * m_Wave.scale;
    Vec3 vWaveRight = Vec3(1,0,0) * m_Wave.scale;
    m_Wave.pVertices[0].p = vOffset + vWaveRight + vWaveUp;
    m_Wave.pVertices[1].p = vOffset - vWaveRight + vWaveUp;
    m_Wave.pVertices[2].p = vOffset + vWaveRight - vWaveUp;
    m_Wave.pVertices[3].p = vOffset - vWaveRight - vWaveUp;
	m_pRenderer->DrawEffectBuffer(&m_Wave.pVertices[0], 0, 4);

    if (m_pLight)
    {
        m_pLight->vPosition = vOffset;
        m_pLight->fIntensity -= (m_fWaveAlphaDec*80.0f);
    }
}


// Start.
void COGEffectExplosion::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

    m_pLight = m_pRenderer->GetLight()->CreatePointLight();
    if (m_pLight)
    {
        m_pLight->vColor = Vec4(1, 1, 0, 1);
        m_pLight->fIntensity = 100.0f;
    }

    m_BBList.clear();
}


// Stop.
void COGEffectExplosion::Stop ()
{
    if (m_pLight)
    {
        m_pRenderer->GetLight()->DestroyPointLight(m_pLight);
        m_pLight = NULL;
    }

    m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BBList.clear();
}
