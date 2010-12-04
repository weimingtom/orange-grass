/*
 *  ogeffectbonuspick.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffectbonuspick.h"
#include "OrangeGrass.h"


float COGEffectBonusPick::m_fAlphaInc;
float COGEffectBonusPick::m_fScaleInc;
float COGEffectBonusPick::m_fInitialScale;
std::string COGEffectBonusPick::m_Texture;
unsigned int COGEffectBonusPick::m_MappingId;
float COGEffectBonusPick::m_fGlowAlphaInc = 0.08f;


COGEffectBonusPick::~COGEffectBonusPick()
{
}


// Load params.
bool COGEffectBonusPick::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/bonuspick.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fAlphaInc = pReader->ReadFloatParam(pRoot, "alpha_inc");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectBonusPick::Init(OGEffectType _Type)
{
	m_GlowEmitter.m_color = Vec4(1.0f, 1.0f, 1.0f, 0.4f);
	m_GlowEmitter.m_fAlphaInc = m_fAlphaInc;
	m_GlowEmitter.m_fGlowAlphaInc = m_fGlowAlphaInc;
	m_GlowEmitter.m_MappingId = 8;
	m_GlowEmitter.m_Texture = m_Texture;
	m_GlowEmitter.Init(NULL);

	m_SparksEmitter.m_color = Vec4(1.0f, 1.0f, 1.0f, 0.5f);
	m_SparksEmitter.m_fAlphaInc = m_fAlphaInc;
	m_SparksEmitter.m_Texture = m_Texture;
    m_SparksEmitter.m_MappingId = m_MappingId;
	m_SparksEmitter.m_fScaleInc = m_fScaleInc;
	m_SparksEmitter.m_fInitialScale = m_fInitialScale;
	m_SparksEmitter.Init(NULL);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectBonusPick::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_GlowEmitter.Update(_ElapsedTime);
	m_SparksEmitter.Update(_ElapsedTime);
	m_Status = m_SparksEmitter.GetStatus();
}


// Render.
void COGEffectBonusPick::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_GlowEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
	m_SparksEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectBonusPick::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	m_GlowEmitter.Start();
	m_SparksEmitter.Start();
}


// Stop.
void COGEffectBonusPick::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;

	m_GlowEmitter.Stop();
	m_SparksEmitter.Stop();
}
