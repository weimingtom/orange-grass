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
#include "ogactorbonus.h"


COGActorBonus::COGActorBonus()
{
	m_pPickEffect = NULL;
	m_pPickNode = NULL;
    m_pBonusParams = NULL;
}


COGActorBonus::~COGActorBonus()
{
    m_pBonusParams = NULL;
	if (m_pPickNode)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pPickNode);
        OG_SAFE_DELETE(m_pPickNode);
	}
}


// Create actor.
bool COGActorBonus::Create (IOGActorParams* _pParams,
                            const OGVec3& _vPos,
                            const OGVec3& _vRot,
                            const OGVec3& _vScale)
{
	m_pParams = _pParams;

	m_pModel = GetResourceMgr()->GetModel(OG_RESPOOL_GAME, m_pParams->model_alias);
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);

	m_pPickEffect = GetEffectsManager()->CreateEffect("bonus_pick");
	m_pPickNode = m_pSg->CreateEffectNode(m_pPickEffect, m_pPhysicalObject);

    Activate(false);
    return true;
}


// Adding to actor manager event handler.
void COGActorBonus::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
	m_pSg->AddNode(m_pNode);
	m_pPhysicalObject->AddCollisionListener(this);

    if (m_pNode)
    {
        m_pNode->StartAnimation("idle");
    }

	if (m_pPickNode)
	{
		GetSceneGraph()->AddEffectNode(m_pPickNode);
        m_pPickNode->Activate(false);
	}
}


// Set active state
void COGActorBonus::Activate (bool _bActive)
{
	if (_bActive == m_bActive || m_Status == OG_ACTORSTATUS_DEAD)
		return;

	COGActor::Activate(_bActive);
	m_pPickNode->Activate(m_bActive);
    if (m_bActive)
    {
        m_pPickEffect->Start();
    }
}


// Update alive actor.
void COGActorBonus::UpdateAlive (unsigned long _ElapsedTime)
{
	COGActor::UpdateAlive(_ElapsedTime);
}


// Update falling actor.
void COGActorBonus::UpdateFalling (unsigned long _ElapsedTime)
{
	COGActor::UpdateFalling(_ElapsedTime);
    m_pNode->Update(_ElapsedTime);

	if (m_pPickEffect)
	{
		if (m_pPickEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE)
		{
			Activate(false);
			m_Status = OG_ACTORSTATUS_DEAD;
		}
	}
	else
	{
		Activate(false);
		m_Status = OG_ACTORSTATUS_DEAD;
	}
}


// collision event handler
bool COGActorBonus::OnCollision (const IOGCollision& _Collision)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE)
        return false;

	m_Status = OG_ACTORSTATUS_FALLING;
	if (m_pPickEffect)
	{
        m_pPickEffect->Stop();
	}
	return true;
}
