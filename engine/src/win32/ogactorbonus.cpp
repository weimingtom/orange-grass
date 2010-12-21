/*
 *  ogactorbonus.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
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
                            const Vec3& _vPos,
                            const Vec3& _vRot,
                            const Vec3& _vScale)
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
