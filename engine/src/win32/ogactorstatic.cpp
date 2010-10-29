/*
 *  ogactorstatic.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorstatic.h"


COGActorStatic::COGActorStatic()
{
}


COGActorStatic::~COGActorStatic()
{
}


// Create actor.
bool COGActorStatic::Create (IOGActorParams* _pParams,
							 const Vec3& _vPos,
							 const Vec3& _vRot,
							 const Vec3& _vScale)
{
	m_pParams = _pParams;
	if (m_pParams->type == OG_ACTOR_NONE)
	{
		OG_LOG_ERROR("Creating COGActorStatic from model %s failed, actor type is OG_ACTOR_NONE", m_pParams->model_alias.c_str());
		return false;
	}

	m_pModel = GetResourceMgr()->GetModel(m_pParams->model_alias);
	if (!m_pModel)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot get model %s", m_pParams->model_alias.c_str());
		return false;
	}
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
    if (!m_pPhysicalObject)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot create physical object");
        return false;
	}
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);
	if (!m_pNode)
	{
		OG_LOG_ERROR("Creating COGActorStatic failed, cannot create SG node");
		return false;
	}

    return true;
}


// Adding to actor manager event handler.
void COGActorStatic::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
	m_pSg->AddStaticNode(m_pNode, m_pModel->GetTexture());
}
