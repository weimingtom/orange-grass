/*
 *  ogactorbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogactorbot.h"


COGActorBot::COGActorBot() :    m_pModelDestruction(NULL),
                                m_pNodeDestruction(NULL),
								m_pExplosionEffect(NULL),
								m_pExplosionNode(NULL),
								m_pWeapon(NULL)
{
}


COGActorBot::~COGActorBot()
{
	if (m_pNodeDestruction)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pNodeDestruction);
        OG_SAFE_DELETE(m_pNodeDestruction);
	}
	if (m_pExplosionNode)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pExplosionNode);
        OG_SAFE_DELETE(m_pExplosionNode);
	}
	//TTrailList::iterator iter = m_TrailList.begin();
	//for (; iter != m_TrailList.end(); ++iter)
	//{
	//	if (m_bAdded)
	//		m_pSg->RemoveNode((*iter).m_pTrailNode);
	//	OG_SAFE_DELETE((*iter).m_pTrailNode);
	//}
	//m_TrailList.clear();

	OG_SAFE_DELETE(m_pWeapon);
}


// Create actor.
bool COGActorBot::Create (IOGActorParams* _pParams,
                          const OGVec3& _vPos,
                          const OGVec3& _vRot,
                          const OGVec3& _vScale)
{
	m_pParams = _pParams;

    m_Hitpoints = m_pParams->gameplay.max_hitpoints;

	m_pModel = GetResourceMgr()->GetModel(OG_RESPOOL_GAME, m_pParams->model_alias);
    if (!m_pParams->model_destruction.empty())
    {
	    m_pModelDestruction = GetResourceMgr()->GetModel(OG_RESPOOL_GAME, m_pParams->model_destruction);
    }
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);
    if (m_pModelDestruction)
    {
	    m_pNodeDestruction = m_pSg->CreateNode(m_pModelDestruction, m_pPhysicalObject);

		//unsigned int NumParts = m_pNodeDestruction->GetTransformedOBBs().size();
		//m_TrailList.reserve(NumParts);
		//for (unsigned int i = 0; i < NumParts; ++i)
		//{
		//	PartsTrail trail;
		//	trail.m_pTrailEffect = GetEffectsManager()->CreateEffect("trail_smoke");
		//	trail.m_pTrailNode = m_pSg->CreateEffectNode(trail.m_pTrailEffect, m_pPhysicalObject);
		//	m_TrailList.push_back(trail);
		//}
	}

	m_pExplosionEffect = GetEffectsManager()->CreateEffect("explosion");
	m_pExplosionNode = m_pSg->CreateEffectNode(m_pExplosionEffect, m_pPhysicalObject);

    SetTeam(m_pParams->gameplay.team);

    if (!m_pParams->gameplay.weapon.empty())
    {
        SetWeapon(GetActorParamsMgr()->GetWeaponParams(m_pParams->gameplay.weapon));
    }

    return true;
}


// Adding to actor manager event handler.
void COGActorBot::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
	m_pSg->AddNode(m_pNode);
    if (m_pModel->HasSubmeshesOfType(OG_SUBMESH_PROPELLER))
    {
        m_pSg->AddTransparentNode(m_pNode);
    }

	m_pPhysicalObject->AddCollisionListener(this);

    if (m_pNodeDestruction)
    {
    	m_pSg->AddNode(m_pNodeDestruction);
        m_pNodeDestruction->Activate(false);
    }

	if (m_pExplosionNode)
	{
		m_pSg->AddEffectNode(m_pExplosionNode);
        m_pExplosionNode->Activate(false);
	}

	//TTrailList::iterator iter = m_TrailList.begin();
	//for (; iter != m_TrailList.end(); ++iter)
	//{
	//	m_pSg->AddEffectNode((*iter).m_pTrailNode);
    //    (*iter).m_pTrailNode->Activate(false);
	//}
}


// collision event handler
bool COGActorBot::OnCollision (const IOGCollision& _Collision)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE)
        return false;

    IOGActor* pMissile = (IOGActor*)_Collision.pActorMissile;
    OGActorType type = pMissile->GetType();
    switch (type)
    {
    case OG_ACTOR_MISSILE:
    case OG_ACTOR_PLASMAMISSILE:
        return RespondOnMissileCollision(pMissile);

    case OG_ACTOR_BONUS:
        return RespondOnBonusCollision(pMissile);

    default:
        return false;
    }

    return false;
}


// Set weapon
void COGActorBot::SetWeapon (IOGWeaponParams* _pWeaponParams)
{
	OG_SAFE_DELETE(m_pWeapon);

	if (_pWeaponParams)
	{
		m_pWeapon = new COGWeapon();
		m_pWeapon->Create(this, _pWeaponParams);
	}
}


// Set active state
void COGActorBot::Activate (bool _bActive)
{
	if (_bActive == m_bActive || m_Status == OG_ACTORSTATUS_DEAD)
		return;

	COGActor::Activate(_bActive);

	if (!m_bActive)
	{
		//TTrailList::iterator iter = m_TrailList.begin();
		//for (; iter != m_TrailList.end(); ++iter)
		//{
		//	(*iter).m_pTrailNode->Activate(false);
		//}

		if (m_pExplosionNode)
			m_pExplosionNode->Activate(false);
	}
}


// Update alive actor.
void COGActorBot::UpdateAlive (unsigned long _ElapsedTime)
{
	COGActor::UpdateAlive(_ElapsedTime);
}


// Update falling actor.
void COGActorBot::UpdateFalling (unsigned long _ElapsedTime)
{
	COGActor::UpdateFalling(_ElapsedTime);

	if (m_pNodeDestruction)
	{
		m_pNodeDestruction->Update(_ElapsedTime);
		
		//const std::vector<IOGObb>& obbslist = m_pNodeDestruction->GetTransformedOBBs();
		//unsigned int NumParts = m_TrailList.size();
		//for (unsigned int i = 0; i < NumParts; ++i)
		//{
		//	m_TrailList[i].m_pTrailEffect->UpdatePosition(obbslist[i].m_vCenter);
		//}
	}
}


// Receive damage
void COGActorBot::ReceiveDamage (unsigned int _Damage)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE || !m_bActive)
        return;

    if (m_Hitpoints > _Damage)
    {
        m_Hitpoints -= _Damage;
    }
    else
    {
        m_Hitpoints = 0;
        SetFallingStatus();
    }
}


// Set actor status.
void COGActorBot::SetFallingStatus ()
{
	if (m_pExplosionNode)
	{
        m_pExplosionNode->Activate(true);
		m_pExplosionEffect->Start();
	}
    if (m_pNodeDestruction)
    {
        m_pNodeDestruction->Activate(true);
        m_pNodeDestruction->StartAnimation("idle");
        m_pNode->Activate(false);
    }
	//TTrailList::iterator iter = m_TrailList.begin();
	//for (; iter != m_TrailList.end(); ++iter)
	//{
	//	(*iter).m_pTrailNode->Activate(true);
	//	(*iter).m_pTrailEffect->Start();
	//	(*iter).m_pTrailEffect->SetDirection(m_pPhysicalObject->GetDirection());
	//}

    m_Status = OG_ACTORSTATUS_FALLING;
}


// Set actor status.
void COGActorBot::SetDeadStatus ()
{
    m_Status = OG_ACTORSTATUS_DEAD;
}


// Respond on collision with missile.
bool COGActorBot::RespondOnMissileCollision (IOGActor* _pMissile)
{
	if (m_Status == OG_ACTORSTATUS_ALIVE)
	{
		unsigned int damage = _pMissile->GetDamagePoints();
		ReceiveDamage(damage);
		return true;
	}
	return false;
}


// Respond on collision with missile.
bool COGActorBot::RespondOnBonusCollision (IOGActor* _pBonus)
{
    return false;
}
