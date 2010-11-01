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


COGEffectCollision::~COGEffectCollision()
{
}


// Initialize effect.
void COGEffectCollision::Init(OGEffectType _Type)
{
    m_MappingStartId = 1;
    m_MappingFinishId = 7;
	m_pTexture = GetResourceMgr()->GetTexture("explosion");
    m_pMaterial = GetMaterialManager()->GetMaterial(OG_MAT_TEXTUREALPHABLEND);

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }
    m_BB.bDirty = true;

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
    float fRotateInc = 0.1f;
	Vec4 color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);

    if (m_BB.bDirty)
    {
        m_BB.bDirty = false;
        m_BB.scale = fInitialScale;
        m_BB.frame = 0.0f;
        m_BB.angle = GetRandomRange(-314,314) * 0.01f;
        m_BB.pVertices[0].c = color;
        m_BB.pVertices[1].c = color;
        m_BB.pVertices[2].c = color;
        m_BB.pVertices[3].c = color;
    }
    else
    {
        if (m_BB.frame < m_Frames.size() - 1)
        {
            m_BB.scale += fScaleInc;
            m_BB.angle += fRotateInc;
            m_BB.frame += fFrameInc;
        }
        else
        {
            Stop();
            return;
        }
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

    Vec3 vSUp = m_vCameraUp * m_BB.scale;
    Vec3 vSRight = m_vCameraRight * m_BB.scale;

    MATRIX mR;
    MatrixRotationAxis(mR, m_BB.angle, m_vCameraLook.x, m_vCameraLook.y, m_vCameraLook.z);

    MatrixVecMultiply(m_BB.pVertices[0].p, vSRight + vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[1].p, -vSRight + vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[2].p, vSRight - vSUp, mR);
    MatrixVecMultiply(m_BB.pVertices[3].p, -vSRight - vSUp, mR);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
    m_BB.pVertices[0].p += vOffset;
    m_BB.pVertices[1].p += vOffset;
    m_BB.pVertices[2].p += vOffset;
    m_BB.pVertices[3].p += vOffset;

    IOGMapping* pMapping = m_Frames[(unsigned int)m_BB.frame];
    m_BB.pVertices[0].t = Vec2(pMapping->t1.x, pMapping->t0.y);
    m_BB.pVertices[1].t = Vec2(pMapping->t0.x, pMapping->t0.y);
    m_BB.pVertices[2].t = Vec2(pMapping->t1.x, pMapping->t1.y);
    m_BB.pVertices[3].t = Vec2(pMapping->t0.x, pMapping->t1.y);

    m_pRenderer->DrawEffectBuffer(&m_BB.pVertices[0], 0, 4);
}


// Start.
void COGEffectCollision::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    m_BB.bDirty = true;
}


// Stop.
void COGEffectCollision::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
    m_BB.bDirty = true;
}
