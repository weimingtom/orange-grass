/*
 *  ogplasmaeffect.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectplasma.h"
#include "OrangeGrass.h"


Vec4 COGEffectPlasma::m_color = Vec4(1.0f, 1.0f, 1.0f, 0.2f);
std::string	COGEffectPlasma::m_Texture = std::string("effects");
unsigned int COGEffectPlasma::m_MappingId = 12;


COGEffectPlasma::~COGEffectPlasma()
{
}


// Initialize effect.
void COGEffectPlasma::Init(OGEffectType _Type)
{
	m_ChainEmitter.m_color = m_color;
    m_ChainEmitter.m_Texture = m_Texture;
    m_ChainEmitter.m_MappingId = m_MappingId;
	m_ChainEmitter.Init();

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectPlasma::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_ChainEmitter.Update(_ElapsedTime);
	m_Status = m_ChainEmitter.GetStatus();
}


// Render.
void COGEffectPlasma::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_ChainEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectPlasma::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	m_ChainEmitter.Start();
}


// Stop.
void COGEffectPlasma::Stop ()
{
	m_Status = OG_EFFECTSTATUS_INACTIVE;
	m_ChainEmitter.Stop();
}


// Set direction.
void COGEffectPlasma::SetDirection (const Vec3& _vDir)
{
	m_ChainEmitter.SetDirection(_vDir);
}
