/*
 *  ogactorairbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorairbot.h"
#include "IOGMath.h"


COGActorAirBot::COGActorAirBot()
{
    m_pExplosionEffect = NULL;
    m_pExplosionNode = NULL;
}


COGActorAirBot::~COGActorAirBot()
{
	if (m_pExplosionNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pExplosionNode);
        else
            OG_SAFE_DELETE(m_pExplosionNode);
		m_pExplosionNode = NULL;
	}
}


// Create actor.
bool COGActorAirBot::Create (IOGActorParams* _pParams,
                             const Vec3& _vPos,
                             const Vec3& _vRot,
                             const Vec3& _vScale)
{
    if (!COGActorBot::Create(_pParams, _vPos, _vRot, _vScale))
        return false;

	m_pExplosionEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_EXPLOSION);
	if (!m_pExplosionEffect)
	{
		OG_LOG_ERROR("Creating COGActorAirBot failed, cannot get effect");
		return false;
	}
	m_pExplosionNode = GetSceneGraph()->CreateNode(m_pExplosionEffect, m_pPhysicalObject);
	if (!m_pExplosionNode)
	{
		OG_LOG_ERROR("Creating COGActorAirBot failed, cannot create SG node");
		return false;
	}

    return true;
}


// Adding to actor manager event handler.
void COGActorAirBot::OnAddedToManager ()
{
    COGActorBot::OnAddedToManager();
    GetSceneGraph()->AddEffectNode(m_pExplosionNode);
    m_pExplosionEffect->Start();
}


// Update actor.
void COGActorAirBot::Update (unsigned long _ElapsedTime)
{
    COGActorBot::Update(_ElapsedTime);
    if (m_pExplosionEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE)
    {
        m_pExplosionEffect->Start();
    }
}
