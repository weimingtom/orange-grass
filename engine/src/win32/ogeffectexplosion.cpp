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

#define MAX_PARTILES 6


COGEffectExplosion::~COGEffectExplosion()
{
}


// Initialize effect.
void COGEffectExplosion::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture("explosion");
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

    m_Frames.reserve(8);
    for (unsigned int i = 0; i < 8; ++i)
    {
        IOGMapping m = *m_pTexture->GetMapping(i+1);
        m_Frames.push_back(m);
    }

    m_BBList.reserve(MAX_PARTILES);
    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectExplosion::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	float fFrameInc = 0.38f;
	float fInitialScale = 8.0f;
	float fScaleInc = 0.05f;
	int numVertsAtOnce = 5;
    float fRotateInc = 0.1f;
	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	int r_min = -4;
	int r_max = 4;

    std::vector<COGExplosionBillboard>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        COGExplosionBillboard& particle = (*iter);
        if (particle.frame < 7)
        {
            particle.scale += fScaleInc;
            particle.angle += fRotateInc;
            particle.frame += fFrameInc;
    		//particle.pVertices[0].c.w -= fAlphaFade;
    		//particle.pVertices[1].c.w -= fAlphaFade;
    		//particle.pVertices[2].c.w -= fAlphaFade;
    		//particle.pVertices[3].c.w -= fAlphaFade;
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

    for (int n = 0; n < numVertsAtOnce; ++n)
    {
        if (m_BBList.size() < MAX_PARTILES-1)
        {
            COGExplosionBillboard particle;
            particle.offset = Vec3(
				(float)GetRandomRange(r_min,r_max),
				(float)GetRandomRange(r_min,r_max),
				(float)GetRandomRange(r_min,r_max));
            particle.scale = fInitialScale;
            particle.frame = 0.0f;
            particle.angle = GetRandomRange(-314,314) * 0.01f;
            particle.bDirty = true;
            particle.pVertices[0].c = color;
            particle.pVertices[1].c = color;
            particle.pVertices[2].c = color;
            particle.pVertices[3].c = color;
            m_BBList.push_back(particle);
        }
    }
}


// Render.
void COGEffectExplosion::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    m_pRenderer->SetModelMatrix(_mWorld);
	m_pRenderer->SetMaterial(m_pMaterial);
	m_pRenderer->SetTexture(m_pTexture);

	OG_LOG_INFO("U [%f, %f, %f], R [%f, %f, %f]", 
		m_vCameraUp.x, m_vCameraUp.y, m_vCameraUp.z, m_vCameraRight.x, m_vCameraRight.y, m_vCameraRight.z);

    std::vector<COGExplosionBillboard>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        COGExplosionBillboard& particle = (*iter);
		Vec3 vSUp = m_vCameraUp * particle.scale;
		Vec3 vSRight = m_vCameraRight * particle.scale;
        if (particle.bDirty)
        {
            particle.bDirty = false;
        }
		particle.pVertices[0].p = vSRight + vSUp;// + particle.offset;
		particle.pVertices[1].p = -vSRight + vSUp;// + particle.offset;
		particle.pVertices[2].p = vSRight - vSUp;// + particle.offset;
		particle.pVertices[3].p = -vSRight - vSUp;// + particle.offset;

        int cur_fr = (int)particle.frame;

        particle.pVertices[0].t = Vec2(m_Frames[cur_fr].t1.x, m_Frames[cur_fr].t0.y);
        particle.pVertices[1].t = Vec2(m_Frames[cur_fr].t0.x, m_Frames[cur_fr].t0.y);
        particle.pVertices[2].t = Vec2(m_Frames[cur_fr].t1.x, m_Frames[cur_fr].t1.y);
        particle.pVertices[3].t = Vec2(m_Frames[cur_fr].t0.x, m_Frames[cur_fr].t1.y);

		float cx = (m_Frames[cur_fr].t1.x - m_Frames[cur_fr].t0.x) / 2.0f + m_Frames[cur_fr].t0.x;
        float cy = (m_Frames[cur_fr].t1.y - m_Frames[cur_fr].t0.y) / 2.0f + m_Frames[cur_fr].t0.y;

		Rotate2DPoint(particle.pVertices[0].t.x, particle.pVertices[0].t.y, particle.angle, cx, cy);
        Rotate2DPoint(particle.pVertices[1].t.x, particle.pVertices[1].t.y, particle.angle, cx, cy);
        Rotate2DPoint(particle.pVertices[2].t.x, particle.pVertices[2].t.y, particle.angle, cx, cy);
        Rotate2DPoint(particle.pVertices[3].t.x, particle.pVertices[3].t.y, particle.angle, cx, cy);

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }
}


// Start.
void COGEffectExplosion::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BBList.clear();
}


// Stop.
void COGEffectExplosion::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BBList.clear();
}
