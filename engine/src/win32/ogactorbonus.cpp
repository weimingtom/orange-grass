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
}


COGActorBonus::~COGActorBonus()
{
	if (m_pNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNode);
        else
            OG_SAFE_DELETE(m_pNode);
		m_pNode = NULL;
	}
	if (m_pPickNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pPickNode);
        else
            OG_SAFE_DELETE(m_pPickNode);
		m_pPickNode = NULL;
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
bool COGActorBonus::Create (IOGActorParams* _pParams,
                            const Vec3& _vPos,
                            const Vec3& _vRot,
                            const Vec3& _vScale)
{
	m_pParams = _pParams;
	if (m_pParams->type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorBonus from model %s failed, actor type is OG_ACTOR_NONE", m_pParams->model_alias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(_pParams->model_alias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorBonus failed, cannot get model %s", m_pParams->model_alias.c_str());
		return false;
	}
	
    m_pPhysicalObject = GetPhysics()->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorBonus failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = GetSceneGraph()->CreateNode(m_pModel, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorBonus failed, cannot create SG node");
		return false;
	}

	//m_pPickEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_BONUSPICK);
	//if (!m_pPickEffect)
	//{
	//	OG_LOG_ERROR("Creating COGActorBonus failed, cannot get effect");
	//	return false;
	//}
	//m_pPickNode = GetSceneGraph()->CreateNode(m_pPickEffect, m_pPhysicalObject);
	//if (!m_pPickNode)
	//{
	//	OG_LOG_ERROR("Creating COGActorBonus failed, cannot create SG node");
	//	return false;
	//}

    Activate(false);

    return true;
}


// Adding to actor manager event handler.
void COGActorBonus::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
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
	if (m_Status == OG_ACTORSTATUS_DEAD || _bActive == m_bActive)
		return;

	COGActor::Activate(_bActive);

	if (m_bActive)
	{
	}
	else
	{
	}
}


// Update actor.
void COGActorBonus::Update (unsigned long _ElapsedTime)
{
	if (m_Status != OG_ACTORSTATUS_DEAD)
		COGActor::Update(_ElapsedTime);

	switch (m_Status)
	{
	case OG_ACTORSTATUS_ALIVE:
		break;

	case OG_ACTORSTATUS_FALLING:
		{
			if (m_pPickEffect)
			{
				if (m_pPickEffect->GetStatus() == OG_EFFECTSTATUS_INACTIVE)
					m_Status = OG_ACTORSTATUS_DEAD;
			}
			else
			{
				m_Status = OG_ACTORSTATUS_DEAD;
			}
		}
		break;

	case OG_ACTORSTATUS_DEAD:
		break;
	}
}


// collision event handler
bool COGActorBonus::OnCollision (const IOGCollision& _Collision)
{
    if (m_Status != OG_ACTORSTATUS_ALIVE)
        return false;

	if (COGActor::OnCollision(_Collision))
	{
		m_Status = OG_ACTORSTATUS_FALLING;
		if (m_pPickEffect)
		{
			m_pPickEffect->Start();
		}
		Activate(false);
		return true;
	}
	return false;
}
