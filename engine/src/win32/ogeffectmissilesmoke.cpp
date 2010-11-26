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


float			COGEffectMissileSmoke::m_fAlphaFade;
float			COGEffectMissileSmoke::m_fInitialScale;
float			COGEffectMissileSmoke::m_fScaleInc;
unsigned int	COGEffectMissileSmoke::m_numVertsAtOnce;
float			COGEffectMissileSmoke::m_fRotateInc;
Vec4			COGEffectMissileSmoke::m_color;
std::string     COGEffectMissileSmoke::m_Texture;
unsigned int    COGEffectMissileSmoke::m_MappingId;
unsigned int    COGEffectMissileSmoke::m_GlowMappingId;


COGEffectMissileSmoke::~COGEffectMissileSmoke()
{
}


// Load params.
bool COGEffectMissileSmoke::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/missilesmoke.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = pReader->OpenGroupNode(pSource, NULL, "Effect");
	if (pRoot)
	{
		m_fAlphaFade = pReader->ReadFloatParam(pRoot, "alpha_fade");
		m_fScaleInc = pReader->ReadFloatParam(pRoot, "scale_inc");
		m_fRotateInc = pReader->ReadFloatParam(pRoot, "rotate_inc");
		m_fInitialScale = pReader->ReadFloatParam(pRoot, "initial_scale");
		m_numVertsAtOnce = (unsigned int)pReader->ReadIntParam(pRoot, "particles_at_once");
		m_Texture = pReader->ReadStringParam(pRoot, "texture");
		m_MappingId = (unsigned int)pReader->ReadIntParam(pRoot, "mapping");
		m_GlowMappingId = (unsigned int)pReader->ReadIntParam(pRoot, "glow_mapping");
		m_color = pReader->ReadVec4Param(pRoot, "r", "g", "b", "a");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectMissileSmoke::Init(OGEffectType _Type)
{
	m_TrailEmitter.m_color = m_color;
	m_TrailEmitter.m_fAlphaFade = m_fAlphaFade;
	m_TrailEmitter.m_fInitialScale = m_fInitialScale;
	m_TrailEmitter.m_fScaleInc = m_fScaleInc;
	m_TrailEmitter.m_numVertsAtOnce = m_numVertsAtOnce;
	m_TrailEmitter.m_fRotateInc = m_fRotateInc;
	m_TrailEmitter.m_Texture = m_Texture;
	m_TrailEmitter.m_MappingId = m_MappingId;
	m_TrailEmitter.Init();

	m_GlowEmitter.m_MappingId = m_GlowMappingId;
	m_GlowEmitter.m_Texture = m_Texture;
	m_GlowEmitter.Init();

	m_bPositionUpdated = false;

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectMissileSmoke::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_TrailEmitter.Update(_ElapsedTime);
	m_GlowEmitter.Update(_ElapsedTime);
	m_Status = m_TrailEmitter.GetStatus();
}


// Update position.
void COGEffectMissileSmoke::UpdatePosition (const Vec3& _vPosition)
{
	COGEffect::UpdatePosition(_vPosition);

	m_TrailEmitter.UpdatePosition(_vPosition);
	m_GlowEmitter.UpdatePosition(_vPosition);
}


// Render.
void COGEffectMissileSmoke::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_TrailEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
	m_GlowEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectMissileSmoke::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	m_TrailEmitter.Start();
	m_GlowEmitter.Start();
}


// Stop.
void COGEffectMissileSmoke::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
	m_TrailEmitter.Stop();
	m_GlowEmitter.Stop();
}
