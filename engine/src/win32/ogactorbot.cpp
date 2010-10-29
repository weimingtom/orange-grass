/*
 *  ogactorbot.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorbot.h"


COGActorBot::COGActorBot() :    m_pModelPropeller(NULL),
                                m_pNodePropeller(NULL),
								m_pModelDestruction(NULL),
                                m_pNodeDestruction(NULL),
								m_pExplosionEffect(NULL),
								m_pExplosionNode(NULL),
								m_pWeapon(NULL)
{
}


COGActorBot::~COGActorBot()
{
	if (m_pNodePropeller)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pNodePropeller);
        else
            OG_SAFE_DELETE(m_pNodePropeller);
		m_pNodePropeller = NULL;
	}
	if (m_pNodeDestruction)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pNodeDestruction);
        else
            OG_SAFE_DELETE(m_pNodeDestruction);
		m_pNodeDestruction = NULL;
	}
	if (m_pExplosionNode)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pExplosionNode);
        else
            OG_SAFE_DELETE(m_pExplosionNode);
		m_pExplosionNode = NULL;
	}
	if (m_pTrailNode)
	{
        if (m_bAdded)
		    m_pSg->RemoveNode(m_pTrailNode);
        else
            OG_SAFE_DELETE(m_pTrailNode);
		m_pTrailNode = NULL;
	}
	OG_SAFE_DELETE(m_pWeapon);
}


// Create actor.
bool COGActorBot::Create (IOGActorParams* _pParams,
                          const Vec3& _vPos,
                          const Vec3& _vRot,
                          const Vec3& _vScale)
{
	m_pParams = _pParams;
	if (m_pParams->type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorBot from model %s failed, actor type is OG_ACTOR_NONE", m_pParams->model_alias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(m_pParams->model_alias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot get model %s", m_pParams->model_alias.c_str());
		return false;
	}
    if (!m_pParams->model_propeller_alias.empty())
    {
	    m_pModelPropeller = GetResourceMgr()->GetModel(m_pParams->model_propeller_alias);
	    if (!m_pModelPropeller)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot get propeller model %s", m_pParams->model_propeller_alias.c_str());
		    return false;
	    }
    }
    if (!m_pParams->model_destruction.empty())
    {
	    m_pModelDestruction = GetResourceMgr()->GetModel(m_pParams->model_destruction);
	    if (!m_pModelDestruction)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot get destruction model %s", m_pParams->model_destruction.c_str());
		    return false;
	    }
    }
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		return false;
	}
    if (m_pModelPropeller)
    {
	    m_pNodePropeller = m_pSg->CreateNode(m_pModelPropeller, m_pPhysicalObject);
	    if (!m_pNodePropeller)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		    return false;
	    }
    }
    if (m_pModelDestruction)
    {
	    m_pNodeDestruction = m_pSg->CreateNode(m_pModelDestruction, m_pPhysicalObject);
	    if (!m_pNodeDestruction)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		    return false;
	    }
    }

	m_pExplosionEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_EXPLOSION);
	if (!m_pExplosionEffect)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot get effect");
		return false;
	}
	m_pExplosionNode = m_pSg->CreateNode(m_pExplosionEffect, m_pPhysicalObject);
	if (!m_pExplosionNode)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		return false;
	}

	m_pTrailEffect = GetEffectsManager()->CreateEffect(OG_EFFECT_MISSILESMOKE);
	m_pTrailNode = m_pSg->CreateNode(m_pTrailEffect, m_pPhysicalObject);

    return true;
}


// Adding to actor manager event handler.
void COGActorBot::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
	m_pSg->AddNode(m_pNode);

	m_pPhysicalObject->AddCollisionListener(this);

    if (m_pNodePropeller)
    {
    	m_pSg->AddTransparentNode(m_pNodePropeller);
        m_pNodePropeller->StartAnimation("idle");
    }

    if (m_pNodeDestruction)
    {
    	m_pSg->AddTransparentNode(m_pNodeDestruction);
        m_pNodeDestruction->Activate(false);
    }

	if (m_pExplosionNode)
	{
		m_pSg->AddEffectNode(m_pExplosionNode);
        m_pExplosionNode->Activate(false);
	}

	if (m_pTrailNode)
	{
		m_pSg->AddEffectNode(m_pTrailNode);
        m_pTrailNode->Activate(false);
	}
}


// collision event handler
bool COGActorBot::OnCollision (const IOGCollision& _Collision)
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
        if (m_pNodePropeller)
        {
            m_pNodePropeller->Activate(false);
        }
    }
    if (m_pTrailNode)
    {
        m_pTrailNode->Activate(true);
        m_pTrailEffect->Start();
        m_pTrailEffect->SetDirection(m_pPhysicalObject->GetDirection());
    }

    return true;
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

	if (m_pNodePropeller)
	{
		m_pNodePropeller->Activate(_bActive);
	}

	if (!m_bActive)
	{
	    if (m_pTrailNode)
			m_pTrailNode->Activate(false);
		if (m_pExplosionNode)
			m_pExplosionNode->Activate(false);
	}
}


// Update alive actor.
void COGActorBot::UpdateAlive (unsigned long _ElapsedTime)
{
	COGActor::UpdateAlive(_ElapsedTime);

	if (m_pNodePropeller)
	{
		m_pNodePropeller->Update(_ElapsedTime);
	}
}


// Update falling actor.
void COGActorBot::UpdateFalling (unsigned long _ElapsedTime)
{
	COGActor::UpdateFalling(_ElapsedTime);

	if (m_pNodeDestruction && m_pTrailEffect)
	{
		m_pNodeDestruction->Update(_ElapsedTime);
		Vec3 vTrail;
		if (m_pNodeDestruction->GetActivePoint(vTrail, "actpointpart02"))
		{
			MatrixVecMultiply(vTrail, vTrail, m_pPhysicalObject->GetWorldTransform());
			m_pTrailEffect->UpdatePosition(vTrail);
		}
	}
}
