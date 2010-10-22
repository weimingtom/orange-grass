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
#include "IOGMath.h"


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
	if (m_pNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNode);
        else
            OG_SAFE_DELETE(m_pNode);
		m_pNode = NULL;
	}
	if (m_pNodePropeller)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNodePropeller);
        else
            OG_SAFE_DELETE(m_pNodePropeller);
		m_pNodePropeller = NULL;
	}
	if (m_pNodeDestruction)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNodeDestruction);
        else
            OG_SAFE_DELETE(m_pNodeDestruction);
		m_pNodeDestruction = NULL;
	}
	if (m_pExplosionNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pExplosionNode);
        else
            OG_SAFE_DELETE(m_pExplosionNode);
		m_pExplosionNode = NULL;
	}
    if (m_pPhysicalObject)
    {
        if (m_bAdded)
            GetPhysics()->RemoveObject(m_pPhysicalObject);
        else
            OG_SAFE_DELETE(m_pPhysicalObject);
        m_pPhysicalObject = NULL;
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

	m_pModel = GetResourceMgr()->GetModel(_pParams->model_alias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot get model %s", m_pParams->model_alias.c_str());
		return false;
	}
    if (!m_pParams->model_propeller_alias.empty())
    {
	    m_pModelPropeller = GetResourceMgr()->GetModel(_pParams->model_propeller_alias);
	    if (!m_pModelPropeller)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot get propeller model %s", m_pParams->model_propeller_alias.c_str());
		    return false;
	    }
    }
    if (!m_pParams->model_destruction.empty())
    {
	    m_pModelDestruction = GetResourceMgr()->GetModel(_pParams->model_destruction);
	    if (!m_pModelDestruction)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot get destruction model %s", m_pParams->model_destruction.c_str());
		    return false;
	    }
    }
	
    m_pPhysicalObject = GetPhysics()->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = GetSceneGraph()->CreateNode(m_pModel, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		return false;
	}
    if (m_pModelPropeller)
    {
	    m_pNodePropeller = GetSceneGraph()->CreateNode(m_pModelPropeller, m_pPhysicalObject);
	    if (!m_pNodePropeller)
	    {
		    OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		    return false;
	    }
    }
    if (m_pModelDestruction)
    {
	    m_pNodeDestruction = GetSceneGraph()->CreateNode(m_pModelDestruction, m_pPhysicalObject);
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
	m_pExplosionNode = GetSceneGraph()->CreateNode(m_pExplosionEffect, m_pPhysicalObject);
	if (!m_pExplosionNode)
	{
		OG_LOG_ERROR("Creating COGActorBot failed, cannot create SG node");
		return false;
	}

    return true;
}


// Adding to actor manager event handler.
void COGActorBot::OnAddedToManager ()
{
    COGActor::OnAddedToManager();

	m_pPhysicalObject->AddCollisionListener(this);

    if (m_pNodePropeller)
    {
    	GetSceneGraph()->AddTransparentNode(m_pNodePropeller);
        m_pNodePropeller->StartAnimation("idle");
    }

    if (m_pNodeDestruction)
    {
    	GetSceneGraph()->AddTransparentNode(m_pNodeDestruction);
        m_pNodeDestruction->Activate(false);
    }

	if (m_pExplosionNode)
	{
		GetSceneGraph()->AddEffectNode(m_pExplosionNode);
	}
}


// Update actor.
void COGActorBot::Update (unsigned long _ElapsedTime)
{
    COGActor::Update(_ElapsedTime);

    if (m_Status == OG_ACTORSTATUS_FALLING)
    {
        m_pNodeDestruction->Update(_ElapsedTime);
    }
    else
    {
        if (m_pNodePropeller)
        {
    	    m_pNodePropeller->Update(_ElapsedTime);
        }
    }
}


// collision event handler
bool COGActorBot::OnCollision (const IOGCollision& _Collision)
{
	if (m_pExplosionNode)
	{
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

    return true;
}


// Set weapon
void COGActorBot::SetWeapon (const std::string& _WeaponAlias)
{
	OG_SAFE_DELETE(m_pWeapon);

	m_pWeapon = new COGWeapon();
    m_pWeapon->Create(this, _WeaponAlias);
}


// Set active state
void COGActorBot::Activate (bool _bActive)
{
	COGActor::Activate(_bActive);
	if (m_pNodePropeller)
	{
		m_pNodePropeller->Activate(_bActive);
	}
}
