/*
 *  ogeffectcollision.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectcollision.h"
#include "OrangeGrass.h"

#define MAX_PARTILES 1


COGEffectCollision::~COGEffectCollision()
{
}


// Initialize effect.
void COGEffectCollision::Init(OGEffectType _Type)
{
	m_pTexture = GetResourceMgr()->GetTexture("explosion");
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

    m_Frames.reserve(7);
    for (unsigned int i = 0; i < 7; ++i)
    {
        IOGMapping m = *m_pTexture->GetMapping(i+1);
        m_Frames.push_back(m);
    }
    m_BBList.reserve(MAX_PARTILES);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectCollision::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	float fFrameInc = 0.38f;
	float fInitialScale = 1.0f;
	float fScaleInc = 0.3f;
	int numVertsAtOnce = MAX_PARTILES;
    float fRotateInc = 0.1f;
	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	int r_min = -1;
	int r_max = 1;

    std::vector<COGCollisionBillboard>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        COGCollisionBillboard& particle = (*iter);
        if (particle.frame < m_Frames.size() - 1)
        {
            particle.scale += fScaleInc;
            particle.angle += fRotateInc;
            particle.frame += fFrameInc;
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

    if (m_BBList.size() < MAX_PARTILES)
    {
        COGCollisionBillboard particle;
        particle.offset = Vec3(
            (float)GetRandomRange(r_min,r_max),
            (float)GetRandomRange(r_min,r_max),
            (float)GetRandomRange(r_min,r_max));
        particle.scale = fInitialScale;
        particle.frame = 0.0f;
        particle.angle = GetRandomRange(-314,314) * 0.01f;
        particle.pVertices[0].c = color;
        particle.pVertices[1].c = color;
        particle.pVertices[2].c = color;
        particle.pVertices[3].c = color;
        m_BBList.push_back(particle);
    }
}


// Render.
void COGEffectCollision::Render (const MATRIX& _mWorld, unsigned int _Frame)
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
    std::vector<COGCollisionBillboard>::iterator iter = m_BBList.begin();
    for (; iter != m_BBList.end(); ++iter)
    {
        COGCollisionBillboard& particle = (*iter);

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

        int cur_fr = (int)particle.frame;

        particle.pVertices[0].t = Vec2(m_Frames[cur_fr].t1.x, m_Frames[cur_fr].t0.y);
        particle.pVertices[1].t = Vec2(m_Frames[cur_fr].t0.x, m_Frames[cur_fr].t0.y);
        particle.pVertices[2].t = Vec2(m_Frames[cur_fr].t1.x, m_Frames[cur_fr].t1.y);
        particle.pVertices[3].t = Vec2(m_Frames[cur_fr].t0.x, m_Frames[cur_fr].t1.y);

		m_pRenderer->DrawEffectBuffer(&particle.pVertices[0], 0, 4);
    }
}


// Start.
void COGEffectCollision::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BBList.clear();
}


// Stop.
void COGEffectCollision::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BBList.clear();
}
