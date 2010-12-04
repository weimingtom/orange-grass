/*
 *  ogemitteranimatedbb.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogemitteranimatedbb.h"
#include "OrangeGrass.h"


COGEmitterAnimatedBB::COGEmitterAnimatedBB()
{
	m_Texture = std::string("effects");
	m_MappingStartId = 1;
	m_MappingFinishId = 7;
	m_fInitialAngleMin = -3.14f;
	m_fInitialAngleMax = 3.14f;
	m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_fFrameInc = 0.5f;
	m_fInitialScale = 8.0f;
	m_fScaleInc = 0.6f;
	m_fRotateInc = 0.1f;

	AddStringParam("texture", &m_Texture);
	AddIntParam("mapping_start", &m_MappingStartId);
	AddIntParam("mapping_finish", &m_MappingFinishId);
	AddFloatParam("init_angle_min", &m_fInitialAngleMin);
	AddFloatParam("init_angle_max", &m_fInitialAngleMax);
	AddFloatParam("init_scale", &m_fInitialScale);
	AddFloatParam("scale_inc", &m_fScaleInc);
	AddFloatParam("frame_inc", &m_fFrameInc);
	AddFloatParam("rotate_inc", &m_fRotateInc);
	AddColorParam("color", &m_color);
}


COGEmitterAnimatedBB::~COGEmitterAnimatedBB()
{
}


// Initialize emitter.
void COGEmitterAnimatedBB::Init(IOGGroupNode* _pNode)
{
	LoadParams(_pNode);

	m_pTexture = GetResourceMgr()->GetTexture(m_Texture);
    m_Blend = OG_BLEND_ALPHAADD;

    m_Frames.reserve(m_MappingFinishId - m_MappingStartId + 1);
    for (unsigned int i = m_MappingStartId; i <= m_MappingFinishId; ++i)
    {
        m_Frames.push_back(m_pTexture->GetMapping(i));
    }

	m_BB.offset = Vec3(0,0,0);
	m_BB.pVertices[0].c = m_color;
	m_BB.pVertices[1].c = m_color;
	m_BB.pVertices[2].c = m_color;
	m_BB.pVertices[3].c = m_color;

	m_bPositionUpdated = false;
}


// Update.
void COGEmitterAnimatedBB::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	if (m_BB.frame < m_Frames.size() - 1)
	{
		m_BB.scale += m_fScaleInc;
		m_BB.angle += m_fRotateInc;
		m_BB.frame += m_fFrameInc;
	}
	else
	{
		Stop();
		return;
	}
}


// Render.
void COGEmitterAnimatedBB::Render (const MATRIX& _mWorld, const Vec3& _vLook, const Vec3& _vUp, const Vec3& _vRight)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    MATRIX mId; 
    MatrixIdentity(mId);
    m_pRenderer->SetModelMatrix(mId);
	m_pRenderer->SetBlend(m_Blend);
	m_pRenderer->SetTexture(m_pTexture);

	Vec3 vSUp = _vUp * m_BB.scale;
	Vec3 vSRight = _vRight * m_BB.scale;

    MATRIX mR;
	MatrixRotationAxis(mR, m_BB.angle, _vLook.x, _vLook.y, _vLook.z);

	MatrixVecMultiply(m_BB.pVertices[0].p, vSRight + vSUp, mR);
	MatrixVecMultiply(m_BB.pVertices[1].p, -vSRight + vSUp, mR);
	MatrixVecMultiply(m_BB.pVertices[2].p, vSRight - vSUp, mR);
	MatrixVecMultiply(m_BB.pVertices[3].p, -vSRight - vSUp, mR);

    Vec3 vOffset = Vec3(_mWorld.f[12], _mWorld.f[13], _mWorld.f[14]);
	m_BB.pVertices[0].p += m_BB.offset + vOffset;
	m_BB.pVertices[1].p += m_BB.offset + vOffset;
	m_BB.pVertices[2].p += m_BB.offset + vOffset;
	m_BB.pVertices[3].p += m_BB.offset + vOffset;

	IOGMapping* pMapping = m_Frames[(unsigned int)m_BB.frame];
	m_BB.pVertices[0].t = Vec2(pMapping->t1.x, pMapping->t0.y);
	m_BB.pVertices[1].t = Vec2(pMapping->t0.x, pMapping->t0.y);
	m_BB.pVertices[2].t = Vec2(pMapping->t1.x, pMapping->t1.y);
	m_BB.pVertices[3].t = Vec2(pMapping->t0.x, pMapping->t1.y);

	m_pRenderer->DrawEffectBuffer(&m_BB.pVertices[0], 0, 4);
}


// Start.
void COGEmitterAnimatedBB::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

	m_BB.scale = m_fInitialScale;
	m_BB.frame = 0.0f;
	m_BB.angle = GetRandomRange(
		(int)(m_fInitialAngleMin * 100.0f), 
		(int)(m_fInitialAngleMax * 100.0f)) * 0.01f;
}


// Stop.
void COGEmitterAnimatedBB::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_INACTIVE;
}
