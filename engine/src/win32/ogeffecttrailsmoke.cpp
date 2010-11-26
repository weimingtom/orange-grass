/*
 *  ogeffecttrailsmoke.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogeffecttrailsmoke.h"
#include "OrangeGrass.h"


float			COGEffectTrailSmoke::m_fAlphaFade;
float			COGEffectTrailSmoke::m_fInitialScale;
float			COGEffectTrailSmoke::m_fScaleInc;
unsigned int	COGEffectTrailSmoke::m_numVertsAtOnce;
float			COGEffectTrailSmoke::m_fRotateInc;
Vec4			COGEffectTrailSmoke::m_color;
std::string     COGEffectTrailSmoke::m_Texture;
unsigned int    COGEffectTrailSmoke::m_MappingId;


COGEffectTrailSmoke::~COGEffectTrailSmoke()
{
}


// Load params.
bool COGEffectTrailSmoke::LoadParams ()
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/trailsmoke.xml"));
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
		m_color = pReader->ReadVec4Param(pRoot, "r", "g", "b", "a");
    	pReader->CloseGroupNode(pRoot);
	}
	pReader->CloseSource(pSource);
	return true;
}


// Initialize effect.
void COGEffectTrailSmoke::Init(OGEffectType _Type)
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

	m_bPositionUpdated = false;
    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectTrailSmoke::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_TrailEmitter.Update(_ElapsedTime);
	m_Status = m_TrailEmitter.GetStatus();
}


// Update position.
void COGEffectTrailSmoke::UpdatePosition (const Vec3& _vPosition)
{
	COGEffect::UpdatePosition(_vPosition);

	m_TrailEmitter.UpdatePosition(_vPosition);
}


// Render.
void COGEffectTrailSmoke::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_TrailEmitter.Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
}


// Start.
void COGEffectTrailSmoke::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
	m_TrailEmitter.Start();
}


// Stop.
void COGEffectTrailSmoke::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;
	m_TrailEmitter.Stop();
}
