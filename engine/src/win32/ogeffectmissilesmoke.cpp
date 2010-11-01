/*
 *  ogeffectmissilesmoke.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectmissilesmoke.h"
#include "OrangeGrass.h"


COGEffectMissileSmoke::~COGEffectMissileSmoke()
{
}


// Initialize effect.
void COGEffectMissileSmoke::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture("smoke_01");
	m_pMapping = m_pTexture->GetMapping(0);
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

	m_bPositionUpdated = false;
    m_BBList.reserve(60);
    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectMissileSmoke::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	float fAlphaFade = 0.01f;
	float fInitialScale = 2.0f;
	float fScaleInc = 0.1f;
	int numVertsAtOnce = 3;
	unsigned int maxSmokeParticles = 60;
    float fRotateInc = 0.1f;
	Vec4 color = Vec4(0.6f, 0.6f, 0.6f, 0.2f);

    std::vector<COGSmokeBillboard>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        COGSmokeBillboard& particle = (*iter);
        if (particle.pVertices[0].c.w >= fAlphaFade)
        {
            particle.scale += fScaleInc;
            particle.angle += fRotateInc;
    		particle.pVertices[0].c.w -= fAlphaFade;
    		particle.pVertices[1].c.w -= fAlphaFade;
    		particle.pVertices[2].c.w -= fAlphaFade;
    		particle.pVertices[3].c.w -= fAlphaFade;
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

		for (int n = 0; n < numVertsAtOnce; ++n)
		{
			//if (m_BBList.size() < maxSmokeParticles-1)
			{
				COGSmokeBillboard particle;
				particle.offset = vDir * (fDist * (float)n);
				particle.scale = fInitialScale;
                particle.angle = rand() * 0.01f;
				particle.bDirty = true;
				particle.pVertices[0].c = color;
				particle.pVertices[1].c = color;
				particle.pVertices[2].c = color;
				particle.pVertices[3].c = color;
				m_BBList.push_back(particle);
			}
		}
	}
}


// Update position.
void COGEffectMissileSmoke::UpdatePosition (const Vec3& _vPosition)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (!m_bPositionUpdated)
	{
		m_vCurPosition = _vPosition;
		m_vPrevPosition = _vPosition;
		m_bPositionUpdated = true;
	}
	else
	{
		m_vPrevPosition = m_vCurPosition;
		m_vCurPosition = _vPosition;
	}
}


// Render.
void COGEffectMissileSmoke::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

    MATRIX mR;
	BBVert* pVert = NULL;
    std::vector<COGSmokeBillboard>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        COGSmokeBillboard& particle = (*iter);
        if (particle.bDirty)
        {
            particle.offset += m_vCurPosition;
            particle.bDirty = false;
        }

        MatrixRotationAxis(mR, particle.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

        Vec3 vSUp = m_vCameraUp * particle.scale;
		Vec3 vSRight = m_vCameraRight * particle.scale;

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
void COGEffectMissileSmoke::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BBList.clear();
}


// Stop.
void COGEffectMissileSmoke::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
}
