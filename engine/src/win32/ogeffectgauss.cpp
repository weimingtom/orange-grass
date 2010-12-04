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
float COGEffectGauss::m_fSegment = 50.0f;
float COGEffectGauss::m_fScale = 8.0f;
float COGEffectGauss::m_fSpeed = 1.0f;
Vec4 COGEffectGauss::m_color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);


COGEffectGauss::~COGEffectGauss()
{
}


// Initialize effect.
void COGEffectGauss::Init(OGEffectType _Type)
{
    m_Blend = OG_BLEND_ALPHAADD;

	m_RayEmitter.m_MappingStartId = m_MappingStartId;
	m_RayEmitter.m_MappingFinishId = m_MappingFinishId;
    m_RayEmitter.m_fSegment = m_fSegment;
    m_RayEmitter.m_fScale = m_fScale;
    m_RayEmitter.m_fSpeed = m_fSpeed;
	m_RayEmitter.m_Texture = m_Texture;
	m_RayEmitter.m_color = m_color;
	m_RayEmitter.Init(NULL);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectGauss::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_RayEmitter.Update(_ElapsedTime);
	m_Status = m_RayEmitter.GetStatus();
}


// Render.
void COGEffectGauss::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_RayEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectGauss::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	m_RayEmitter.Start();
}


// Stop.
void COGEffectGauss::Stop ()
{
    m_Status = OG_EFFECTSTATUS_INACTIVE;
	m_RayEmitter.Stop();
}


// Set start and finish positions.
void COGEffectGauss::SetStartFinishPositions (const Vec3& _vStartPos, const Vec3& _vFinishPos)
{
	m_RayEmitter.SetStartFinishPositions(_vStartPos, _vFinishPos);
}
