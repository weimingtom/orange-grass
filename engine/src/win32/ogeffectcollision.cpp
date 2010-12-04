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


unsigned int COGEffectCollision::m_MappingStartId;
unsigned int COGEffectCollision::m_MappingFinishId;
float COGEffectCollision::m_fFrameInc;
float COGEffectCollision::m_fInitialScale;
float COGEffectCollision::m_fScaleInc;
float COGEffectCollision::m_fRotateInc;
std::string COGEffectCollision::m_Texture;

float COGEffectCollision::m_fLightFadeFactor = 0.1f;
float COGEffectCollision::m_fLightInitialIntensity = 20.0f;


COGEffectCollision::~COGEffectCollision()
{
}


// Load params.
bool COGEffectCollision::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/collision.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fFrameInc = pReader->ReadFloatParam(pRoot, "frame_inc");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fRotateInc = pReader->ReadFloatParam(pRoot, "rotate_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingStartId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping_start");
		m_MappingFinishId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping_finish");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectCollision::Init(OGEffectType _Type)
{
	m_AnimatedBBEmitter.m_Texture = m_Texture;
	m_AnimatedBBEmitter.m_MappingStartId = m_MappingStartId;
	m_AnimatedBBEmitter.m_MappingFinishId = m_MappingFinishId;
	m_AnimatedBBEmitter.m_fFrameInc = m_fFrameInc;
	m_AnimatedBBEmitter.m_fInitialScale = m_fInitialScale;
	m_AnimatedBBEmitter.m_fScaleInc = m_fScaleInc;
	m_AnimatedBBEmitter.m_fRotateInc = m_fRotateInc;
	m_AnimatedBBEmitter.Init(NULL);

	m_LightFlashEmitter.m_fFadeFactor = m_fLightFadeFactor;
	m_LightFlashEmitter.m_fInitialIntensity = m_fLightInitialIntensity;
	m_LightFlashEmitter.Init(NULL);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectCollision::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_AnimatedBBEmitter.Update(_ElapsedTime);
	m_LightFlashEmitter.Update(_ElapsedTime);
	m_Status = m_AnimatedBBEmitter.GetStatus();
}


// Render.
void COGEffectCollision::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_AnimatedBBEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
	m_LightFlashEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectCollision::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;

	m_AnimatedBBEmitter.Start();
	m_LightFlashEmitter.Start();
}


// Stop.
void COGEffectCollision::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    m_Status = OG_EFFECTSTATUS_INACTIVE;

	m_AnimatedBBEmitter.Stop();
	m_LightFlashEmitter.Stop();
}
