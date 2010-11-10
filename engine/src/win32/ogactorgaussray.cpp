/*
 *  ogactorgaussray.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorgaussray.h"


COGActorGaussRay::COGActorGaussRay()
{
    m_pHeadEffect = NULL;
}


COGActorGaussRay::~COGActorGaussRay()
{
}


// Create actor.
bool COGActorGaussRay::Create (IOGActorParams* _pParams,
                               const Vec3& _vPos,
                               const Vec3& _vRot,
                               const Vec3& _vScale)
{
	m_pParams = _pParams;

	if (m_pParams->type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorGaussRay from model %s failed, actor type is OG_ACTOR_NONE", m_pParams->model_alias.c_str());
		return false;
	}

	m_pHeadEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_GAUSS);
	if (!m_pHeadEffect)
	{
		OG_LOG_ERROR("Creating COGActorGaussRay failed, cannot get effect %s", m_pParams->model_alias.c_str());
		return false;
	}
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pHeadEffect->GetAABB(), this);
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorGaussRay failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pHeadEffect, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorGaussRay failed, cannot create SG node");
		return false;
	}

    m_pCollisionEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_COLLISION);
	m_pCollisionEffectNode = m_pSg->CreateNode(m_pCollisionEffect, m_pPhysicalObject);

    Activate(false);
	return true;
}


// Adding to actor manager event handler.
void COGActorGaussRay::OnAddedToManager ()
{
    COGActor::OnAddedToManager();

	m_pSg->AddEffectNode(m_pNode);
    m_pPhysicalObject->AddCollisionListener(this);

    m_pSg->AddEffectNode(m_pCollisionEffectNode);
    m_pCollisionEffectNode->Activate(false);
}


// Update alive actor.
void COGActorGaussRay::UpdateAlive (unsigned long _ElapsedTime)
{
}


// Update falling actor.
void COGActorGaussRay::UpdateFalling (unsigned long _ElapsedTime)
{
}


// Set active state
void COGActorGaussRay::Activate (bool _bActive)
{
    if (_bActive == m_bActive)
        return;

	COGActorBullet::Activate(_bActive);

	if (m_bActive)
	{
		m_Status = OG_ACTORSTATUS_ALIVE;
		m_pHeadEffect->Start();
		m_pHeadEffect->SetDirection(Vec3(0,0,1));
        m_pHeadEffect->SetStartFinishPositions(m_vLaunchOffset, m_vTarget);
        m_pPhysicalObject->Update(1);
	}
	else
	{
        m_pCollisionEffectNode->Activate(false);
	}
}


// Fire.
void COGActorGaussRay::Fire ()
{
	COGActorBullet::Fire();

    Vec3 vRot = m_pOwner->GetPhysicalObject()->GetRotation();
	m_pPhysicalObject->SetWorldTransform(m_vLaunchOffset, vRot, Vec3(1,1,1));
    Activate(true);

}


// collision event handler
bool COGActorGaussRay::OnCollision (const IOGCollision& _Collision)
{
	if (!m_bActive || m_Status != OG_ACTORSTATUS_ALIVE)
		return false;

    return false;
}


// Set target.
void COGActorGaussRay::SetTarget (const Vec3& _vTarget)
{
    COGActorBullet::SetTarget(_vTarget);
}
