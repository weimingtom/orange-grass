/*
 *  ogactorplasmamissile.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorplasmamissile.h"
#include "IOGMath.h"


COGActorPlasmaMissile::COGActorPlasmaMissile()
{
}


COGActorPlasmaMissile::~COGActorPlasmaMissile()
{
	if (m_pNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNode);
        else
            OG_SAFE_DELETE(m_pNode);
		m_pNode = NULL;
	}
    if (m_pPhysicalObject)
    {
        if (m_bAdded)
            GetPhysics()->RemoveObject(m_pPhysicalObject);
        else
            OG_SAFE_DELETE(m_pPhysicalObject);
        m_pPhysicalObject = NULL;
    }
}


// Create actor.
bool COGActorPlasmaMissile::Create (IOGActorParams* _pParams,
                                    const Vec3& _vPos,
                                    const Vec3& _vRot,
                                    const Vec3& _vScale)
{
	m_pParams = _pParams;

	if (m_pParams->type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorPlasmaMissile from model %s failed, actor type is OG_ACTOR_NONE", _pParams->model_alias.c_str());
		return false;
	}

	m_pHeadEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_PLASMA);
	if (!m_pHeadEffect)
	{
		OG_LOG_ERROR("Creating COGActorPlasmaMissile failed, cannot get effect %s", _pParams->model_alias.c_str());
		return false;
	}
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_AIRBOT, m_pHeadEffect->GetAABB());
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorPlasmaMissile failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = GetSceneGraph()->CreateNode(m_pHeadEffect, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorPlasmaMissile failed, cannot create SG node");
		return false;
	}

	return true;
}


// Adding to actor manager event handler.
void COGActorPlasmaMissile::OnAddedToManager ()
{
    GetPhysics()->AddObject(m_pPhysicalObject);
    GetSceneGraph()->AddEffectNode(m_pNode);
	m_pHeadEffect->Start();
	m_pHeadEffect->SetDirection(Vec3(0,0,1));
    m_bAdded = true;
}


// Update actor.
void COGActorPlasmaMissile::Update (unsigned long _ElapsedTime)
{
    m_pPhysicalObject->Accelerate(1.0f);
}
