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


COGEmitterTrail::COGEmitterTrail()
{
    m_Texture = std::string("effects");
    m_MappingId = 5;
	m_numVertsAtOnce = 3;
	m_fAlphaFade = 0.01f;
	m_fInitialScale = 2.0f;
	m_fScaleInc = 0.1f;
    m_fRotateInc = 0.1f;
	m_color = Vec4(0.6f, 0.6f, 0.6f, 0.2f);

	AddStringParam("texture", &m_Texture);
	AddIntParam("mapping", &m_MappingId);
	AddIntParam("particles_at_once", &m_numVertsAtOnce);
	AddFloatParam("alpha_fade", &m_fAlphaFade);
	AddFloatParam("scale_inc", &m_fScaleInc);
	AddFloatParam("rotate_inc", &m_fRotateInc);
	AddFloatParam("init_scale", &m_fInitialScale);
	AddColorParam("color", &m_color);
}


COGEmitterTrail::~COGEmitterTrail()
{
}


// Initialize emitter.
void COGEmitterTrail::Init(IOGGroupNode* _pNode)
{
	LoadParams(_pNode);

	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
	m_pMapping = m_pTexture->GetMapping(m_MappingId);
    m_Blend = OG_BLEND_ALPHABLEND;

	m_bPositionUpdated = false;
    m_BBList.reserve(60);
}


// Update.
void COGEmitterTrail::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        ParticleFormat& particle = (*iter);
        if (particle.pVertices[0].c.w >= m_fAlphaFade)
        {
            particle.scale += m_fScaleInc;
            particle.angle += m_fRotateInc;
    		particle.pVertices[0].c.w -= m_fAlphaFade;
    		particle.pVertices[1].c.w -= m_fAlphaFade;
    		particle.pVertices[2].c.w -= m_fAlphaFade;
    		particle.pVertices[3].c.w -= m_fAlphaFade;
            ++iter;
        }
        else
        {
            iter = m_BBList.erase(iter);
            if (m_BBList.empty())
            {
                m_Status = OG_EFFECTSTATUS_INACTIVE;
                return;
            }
        }
    }

	if (m_Status == OG_EFFECTSTATUS_STARTED && m_bPositionUpdated && m_vCurPosition != m_vPrevPosition)
	{
		Vec3 vDir = m_vPrevPosition - m_vCurPosition;
		float fDist = vDir.length();
		vDir.normalize();

		for (unsigned int n = 0; n < m_numVertsAtOnce; ++n)
		{
			ParticleFormat particle;
			particle.offset = vDir * (fDist * (float)n);
			particle.scale = m_fInitialScale;
			particle.angle = rand() * 0.01f;
			particle.bDirty = true;
			particle.pVertices[0].c = m_color;
			particle.pVertices[1].c = m_color;
			particle.pVertices[2].c = m_color;
			particle.pVertices[3].c = m_color;
			m_BBList.push_back(particle);
		}
	}
}


// Render.
void COGEmitterTrail::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

    MATRIX mR;
	BBVert* pVert = NULL;
    std::vector<ParticleFormat>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        ParticleFormat& particle = (*iter);
        if (particle.bDirty)
        {
            particle.offset += m_vCurPosition;
            particle.bDirty = false;
        }

        MatrixRotationAxis(mR, particle.angle, _vLook.x, _vLook.y, _vLook.z);

        Vec3 vSUp = _vUp * particle.scale;
		Vec3 vSRight = _vRight * particle.scale;

		pVert = &particle.pVertices[0];
        MatrixVecMultiply(pVert->p, vSRight + vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t0.y;

		pVert = &particle.pVertices[1];
        MatrixVecMultiply(pVert->p, -vSRight + vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t0.y;

		pVert = &particle.pVertices[2];
        MatrixVecMultiply(pVert->p, vSRight - vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t1.x; pVert->t.y = m_pMapping->t1.y;

		pVert = &particle.pVertices[3];
        MatrixVecMultiply(pVert->p, -vSRight - vSUp, mR);
		pVert->p += particle.offset;
        pVert->t.x = m_pMapping->t0.x; pVert->t.y = m_pMapping->t1.y;

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }
}


// Start.
void COGEmitterTrail::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BBList.clear();
}


// Stop.
void COGEmitterTrail::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
}
