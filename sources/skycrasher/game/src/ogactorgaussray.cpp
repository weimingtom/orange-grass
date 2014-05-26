/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "Game.h"
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
                               const OGVec3& _vPos,
                               const OGVec3& _vRot,
                               const OGVec3& _vScale)
{
	m_pParams = _pParams;

	m_pHeadEffect = GetEffectsManager()->CreateEffect("gauss");
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pHeadEffect->GetAABB(), this);
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateEffectNode(m_pHeadEffect, m_pPhysicalObject);

    m_pCollisionEffect = GetEffectsManager()->CreateEffect("collision");
	m_pCollisionEffectNode = m_pSg->CreateEffectNode(m_pCollisionEffect, m_pPhysicalObject);

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
		m_pHeadEffect->SetDirection(OGVec3(0,0,1));
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

    OGVec3 vRot = m_pOwner->GetPhysicalObject()->GetRotation();
	m_pPhysicalObject->SetWorldTransform(m_vLaunchOffset, vRot, OGVec3(1,1,1));
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
void COGActorGaussRay::SetTarget (const OGVec3& _vTarget)
{
    COGActorBullet::SetTarget(_vTarget);
}
