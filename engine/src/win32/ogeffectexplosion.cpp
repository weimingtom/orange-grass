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


std::string COGEffectExplosion::m_Texture = std::string("effects");
unsigned int COGEffectExplosion::m_MappingStartId = 1;
unsigned int COGEffectExplosion::m_MappingFinishId = 7;
float COGEffectExplosion::m_fFrameInc = 0.5f;
float COGEffectExplosion::m_fInitialScale = 8.0f;
float COGEffectExplosion::m_fScaleInc = 0.6f;
float COGEffectExplosion::m_fRotateInc = 0.1f;

float COGEffectExplosion::m_fWaveInitialScale = 8.0f;
float COGEffectExplosion::m_fWaveAlphaDec = 0.08f;
float COGEffectExplosion::m_fWaveScaleInc = 1.5f;
unsigned int COGEffectExplosion::m_WaveMappingId = 10;

float COGEffectExplosion::m_fLightFadeFactor = 0.64f;
float COGEffectExplosion::m_fLightInitialIntensity = 100.0f;


COGEffectExplosion::~COGEffectExplosion()
{
}


// Initialize effect.
void COGEffectExplosion::Init(OGEffectType _Type)
{
	m_AnimatedBBEmitter.m_Texture = m_Texture;
	m_AnimatedBBEmitter.m_MappingStartId = m_MappingStartId;
	m_AnimatedBBEmitter.m_MappingFinishId = m_MappingFinishId;
	m_AnimatedBBEmitter.m_fFrameInc = m_fFrameInc;
	m_AnimatedBBEmitter.m_fInitialScale = m_fInitialScale;
	m_AnimatedBBEmitter.m_fScaleInc = m_fScaleInc;
	m_AnimatedBBEmitter.m_fRotateInc = m_fRotateInc;
	m_AnimatedBBEmitter.Init();

	m_RingWaveEmitter.m_Texture = m_Texture;
	m_RingWaveEmitter.m_MappingId = m_WaveMappingId;
	m_RingWaveEmitter.m_fWaveInitialScale = m_fWaveInitialScale;
	m_RingWaveEmitter.m_fWaveAlphaDec = m_fWaveAlphaDec;
	m_RingWaveEmitter.m_fWaveScaleInc = m_fWaveScaleInc;
	m_RingWaveEmitter.Init();

	m_LightFlashEmitter.m_fFadeFactor = m_fLightFadeFactor;
	m_LightFlashEmitter.m_fInitialIntensity = m_fLightInitialIntensity;
	m_LightFlashEmitter.Init();

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectExplosion::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_AnimatedBBEmitter.Update(_ElapsedTime);
	m_RingWaveEmitter.Update(_ElapsedTime);
	m_LightFlashEmitter.Update(_ElapsedTime);
	m_Status = m_AnimatedBBEmitter.GetStatus();
}


// Render.
void COGEffectExplosion::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_AnimatedBBEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
	m_RingWaveEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
	m_LightFlashEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectExplosion::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

	m_RingWaveEmitter.Start();
	m_AnimatedBBEmitter.Start();
	m_LightFlashEmitter.Start();
}


// Stop.
void COGEffectExplosion::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    m_Status = OG_EFFECTSTATUS_INACTIVE;

	m_AnimatedBBEmitter.Stop();
	m_RingWaveEmitter.Stop();
	m_LightFlashEmitter.Stop();
}
