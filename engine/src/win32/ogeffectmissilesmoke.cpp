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
    //m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_ALPHATEST);
    //m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_SOLID);

    m_BBList.reserve(MAX_SMOKE_PARTILES);
    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectMissileSmoke::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    std::vector<COSmokeGBillboard>::iterator iter = m_BBList.begin();
    while (iter != m_BBList.end())
    {
        COSmokeGBillboard& particle = (*iter);
        if (particle.pVertices[0].c.w >= 0.05f)
        {
            particle.scale += 0.5f;
    		particle.pVertices[0].c.w -= 0.05f;
    		particle.pVertices[1].c.w -= 0.05f;
    		particle.pVertices[2].c.w -= 0.05f;
    		particle.pVertices[3].c.w -= 0.05f;
            ++iter;
        }
        else
        {
            iter = m_BBList.erase(iter);
        }
    }

    Vec4 color = Vec4(0.6f, 0.6f, 0.6f, 0.9f);
    if (m_BBList.size() < MAX_SMOKE_PARTILES-1)
    {
        COSmokeGBillboard particle;
        particle.offset = Vec3(0,0,0);
        particle.scale = 2.0f;
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
            particle.offset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
            particle.bDirty = false;
        }
		particle.pVertices[0].p = vSRight + vSUp + particle.offset;
		particle.pVertices[1].p = -vSRight + vSUp + particle.offset;
		particle.pVertices[2].p = vSRight - vSUp + particle.offset;
		particle.pVertices[3].p = -vSRight - vSUp + particle.offset;
    }

    int numP = (int)m_BBList.size();
    for (int i = 0; i < numP; ++i)
	{
        int base = i*4;
		COSmokeGBillboard& particle = m_BBList[i];
        m_Vertices[base + 0] = particle.pVertices[0];
        m_Vertices[base + 1] = particle.pVertices[1];
        m_Vertices[base + 2] = particle.pVertices[2];
        m_Vertices[base + 3] = particle.pVertices[3];
        m_pRenderer->DrawEffectBuffer(&m_Vertices[base + 0], 0, 4);
	}

    //m_pRenderer->DrawEffectBuffer(m_Vertices, 0, numP*4);
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
