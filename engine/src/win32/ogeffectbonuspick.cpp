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
#include <functional>


COGEffectBonusPick::~COGEffectBonusPick()
{
}


// Load params.
bool COGEffectBonusPick::LoadParams ()
{
	return true;
}


// Initialize effect.
void COGEffectBonusPick::Init(OGEffectType _Type, const std::string& _File)
{
	IOGSettingsReader* pReader = GetSettingsReader();

    IOGSettingsSource* pSource = pReader->OpenSource(GetResourceMgr()->GetFullPath("Effects/bonuspick.xml"));
	if (!pSource)
		return;

    IOGGroupNode* pEffectNode = pReader->OpenGroupNode(pSource, NULL, "Effect");
    if (pEffectNode)
    {
        IOGGroupNode* pEmitterNode = pReader->OpenGroupNode(pSource, pEffectNode, "Emitter");
        while (pEmitterNode)
        {
            COGEmitter* pEmitter = NULL;

            std::string type_str = pReader->ReadStringParam(pEmitterNode, "type");
            int master = pReader->ReadIntParam(pEmitterNode, "master");

            if (type_str.compare("pulse_glow") == 0) { pEmitter = new COGEmitterPulseGlow(); }
            else if (type_str.compare("rotating_sparks") == 0) { pEmitter = new COGEmitterRotatingSparks(); }

            if (pEmitter)
            {
                pEmitter->Init(pEmitterNode);
                m_Emitters.push_back(pEmitter);
                if (master == 1)
                {
                    m_pMasterEmitter = pEmitter;
                }
            }
            pEmitterNode = pReader->ReadNextNode(pEmitterNode);
        }
    }
    pReader->CloseSource(pSource);

    m_AABB.SetMinMax(Vec3(-1,-1,-1), Vec3(1,1,1));
}


// Update.
void COGEffectBonusPick::Update (unsigned long _ElapsedTime)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Update(_ElapsedTime);
    }
	m_Status = m_pMasterEmitter->GetStatus();
}


// Render.
void COGEffectBonusPick::Render (const MATRIX& _mWorld)
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Render(_mWorld, m_vCameraLook, m_vCameraUp, m_vCameraRight);
    }
}


// Start.
void COGEffectBonusPick::Start ()
{
	m_Status = OG_EFFECTSTATUS_STARTED;
    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Start();
    }
}


// Stop.
void COGEffectBonusPick::Stop ()
{
	if (m_Status == OG_EFFECTSTATUS_INACTIVE)
		return;

	m_Status = OG_EFFECTSTATUS_STOPPED;

    TEmittersList::iterator iter = m_Emitters.begin();
    for (; iter != m_Emitters.end(); ++iter)
    {
        (*iter)->Stop();
    }
}
