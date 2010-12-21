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

	m_pModel = GetResourceMgr()->GetModel(OG_RESPOOL_GAME, m_pParams->model_alias);
	
    m_pPhysicalObject = m_pPhysics->CreateObject(&m_pParams->physics, m_pModel->GetAABB(), this);
	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);

	m_pNode = m_pSg->CreateNode(m_pModel, m_pPhysicalObject);

    return true;
}


// Adding to actor manager event handler.
void COGActorStatic::OnAddedToManager ()
{
    COGActor::OnAddedToManager();
	m_pSg->AddStaticNode(m_pNode, m_pModel->GetTexture());
}
