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
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

	m_bPositionUpdated = false;
    m_BBList.reserve(MAX_SMOKE_PARTILES);
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
    float fRotateInc = 0.1f;
	Vec4 color = Vec4(0.6f, 0.6f, 0.6f, 0.2f);

    std::vector<COSmokeGBillboard>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        COSmokeGBillboard& particle = (*iter);
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
        }
    }

	if (m_bPositionUpdated && m_vCurPosition != m_vPrevPosition)
	{
		Vec3 vDir = m_vPrevPosition - m_vCurPosition;
		float fDist = vDir.length();
		vDir.normalize();

		for (int n = 0; n < numVertsAtOnce; ++n)
		{
			//if (m_BBList.size() < MAX_SMOKE_PARTILES-1)
			{
				COSmokeGBillboard particle;
				particle.offset = vDir * (fDist * (float)n);
				particle.scale = fInitialScale;
                particle.angle = rand() * 0.01f;
				particle.bDirty = true;
				particle.pVertices[0].t = Vec2(1.0f, 0.0f);
				particle.pVertices[0].c = color;
				particle.pVertices[1].t = Vec2(0.0f, 0.0f);
				particle.pVertices[1].c = color;
				particle.pVertices[2].t = Vec2(1.0f, 1.0f);
				particle.pVertices[2].c = color;
				particle.pVertices[3].t = Vec2(0.0f, 1.0f);
				particle.pVertices[3].c = color;
				m_BBList.push_back(particle);
			}
		}
	}
}


// Update position.
void COGEffectMissileSmoke::UpdatePosition (const Vec3& _vPosition)
{
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

    std::vector<COSmokeGBillboard>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        COSmokeGBillboard& particle = (*iter);
		Vec3 vSUp = m_vCameraUp * particle.scale;
		Vec3 vSRight = m_vCameraRight * particle.scale;
        if (particle.bDirty)
        {
            particle.offset += Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
            particle.bDirty = false;
        }
		particle.pVertices[0].p = vSRight + vSUp + particle.offset;
		particle.pVertices[1].p = -vSRight + vSUp + particle.offset;
		particle.pVertices[2].p = vSRight - vSUp + particle.offset;
		particle.pVertices[3].p = -vSRight - vSUp + particle.offset;

        particle.pVertices[0].t = Vec2(1.0f, 0.0f);
        particle.pVertices[1].t = Vec2(0.0f, 0.0f);
        particle.pVertices[2].t = Vec2(1.0f, 1.0f);
        particle.pVertices[3].t = Vec2(0.0f, 1.0f);
        Rotate2DPoint(particle.pVertices[0].t.x, particle.pVertices[0].t.y, particle.angle, 0.5f, 0.5f);
        Rotate2DPoint(particle.pVertices[1].t.x, particle.pVertices[1].t.y, particle.angle, 0.5f, 0.5f);
        Rotate2DPoint(particle.pVertices[2].t.x, particle.pVertices[2].t.y, particle.angle, 0.5f, 0.5f);
        Rotate2DPoint(particle.pVertices[3].t.x, particle.pVertices[3].t.y, particle.angle, 0.5f, 0.5f);

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
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BBList.clear();
}
