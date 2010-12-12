/*
 *  ogactormissile.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactormissile.h"


COGActorMissile::COGActorMissile()
{
    m_pHeadEffect = NULL;
}


COGActorMissile::~COGActorMissile()
{
}


// Create actor.
bool COGActorMissile::Create (IOGActorParams* _pParams,
                              const Vec3& _vPos,
                              const Vec3& _vRot,
                              const Vec3& _vScale)
{
	m_pParams = _pParams;

	m_pHeadEffect = GetEffectsManager()->CreateEffect("missile_smoke");
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pHeadEffect->GetAABB(), this);
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateEffectNode(m_pHeadEffect, m_pPhysicalObject);

    m_pCollisionEffect = GetEffectsManager()->CreateEffect("collision");
	m_pCollisionEffectNode = m_pSg->CreateEffectNode(m_pCollisionEffect, m_pPhysicalObject);

	m_FlightWorker.Create(this);
    Activate(false);

	return true;
}


// Adding to actor manager event handler.
void COGActorMissile::OnAddedToManager ()
{
    COGActor::OnAddedToManager();

	m_pSg->AddEffectNode(m_pNode);
    m_pPhysicalObject->AddCollisionListener(this);

    m_pSg->AddEffectNode(m_pCollisionEffectNode);
    m_pCollisionEffectNode->Activate(false);
}


// Update alive actor.
void COGActorMissile::UpdateAlive (unsigned long _ElapsedTime)
{
	if (m_FlightWorker.IsActive())
	{
        m_pHeadEffect->UpdatePosition(m_pPhysicalObject->GetPosition());
		m_FlightWorker.Update(_ElapsedTime);
		if (m_FlightWorker.IsFinished())
		{
			m_pPhysicalObject->Activate(false);
			m_pHeadEffect->Stop();
			m_Status = OG_ACTORSTATUS_FALLING;
		}
	}
	else
	{
		m_pPhysicalObject->Activate(false);
		m_pHeadEffect->Stop();
		m_Status = OG_ACTORSTATUS_FALLING;
	}
}


// Update falling actor.
void COGActorMissile::UpdateFalling (unsigned long _ElapsedTime)
{
	if (m_pHeadEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE && 
        m_pCollisionEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE)
	{
		Activate(false);
	}
}


// Set active state
void COGActorMissile::Activate (bool _bActive)
{
    if (_bActive == m_bActive)
        return;

	COGActorBullet::Activate(_bActive);

	if (m_bActive)
	{
		m_Status = OG_ACTORSTATUS_ALIVE;
		m_FlightWorker.Reset();
		m_FlightWorker.Activate(true);
		m_pHeadEffect->Start();
		m_pHeadEffect->SetDirection(Vec3(0,0,1));
        m_pPhysicalObject->Update(1);
	}
	else
	{
        m_pCollisionEffectNode->Activate(false);
	}
}


// Fire.
void COGActorMissile::Fire ()
{
	COGActorBullet::Fire();

    Vec3 vRot = m_pOwner->GetPhysicalObject()->GetRotation();
	m_pPhysicalObject->SetWorldTransform(m_vLaunchOffset, vRot, Vec3(1,1,1));
    Activate(true);
}


// Set target.
void COGActorMissile::SetTarget (const Vec3& _vTarget)
{
    COGActorBullet::SetTarget(_vTarget);
    m_FlightWorker.SetTarget(_vTarget);
}


// Set target.
void COGActorMissile::SetTarget (IOGActor* _pTarget)
{
    COGActorBullet::SetTarget(_pTarget);
    m_FlightWorker.SetTarget(_pTarget);
}


// collision event handler
bool COGActorMissile::OnCollision (const IOGCollision& _Collision)
{
	if (!m_bActive || m_Status != OG_ACTORSTATUS_ALIVE)
		return false;

	m_pPhysicalObject->Activate(false);
	m_FlightWorker.Activate(false);
	m_Status = OG_ACTORSTATUS_FALLING;
	m_pHeadEffect->Stop();

    m_pCollisionEffectNode->Activate(true);
	m_pCollisionEffect->SetDirection(Vec3(0,0,1));
    m_pCollisionEffect->Start();

    return true;
}
