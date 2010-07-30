/*
 *  ogscenegraph.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
#include "ogactor.h"
#include "IOGMath.h"


COGActor::COGActor() :	m_pNode(NULL),
						m_Type(OG_ACTOR_NONE)
{
}


COGActor::COGActor(OGActorType _Type) : m_pNode(NULL),
										m_Type(_Type)
{
}


COGActor::~COGActor()
{
	if (m_pNode)
	{
		GetSceneGraph()->RemoveNode(m_pNode);
		m_pNode = NULL;
	}
}


// Create actor.
bool COGActor::Create (const char* _pModelAlias,
					   const Vec3& _vPos,
					   const Vec3& _vRot)
{
	if (m_Type == OG_ACTOR_NONE)
		return false;

	IOGModel* pModel = GetResourceMgr()->GetModel(_pModelAlias);
	if (!pModel)
		return false;

	m_pNode = GetSceneGraph()->CreateNode(pModel);
	if (!m_pNode)
		return false;
	
	m_pNode->SetWorldTransform(_vPos, _vRot);
	GetSceneGraph()->AddNode(m_pNode);

	return true;
}


// Create actor.
bool COGActor::Create (const char* _pModelAlias,
					   const MATRIX& _mWorld)
{
	IOGModel* pModel = GetResourceMgr()->GetModel(_pModelAlias);
	if (!pModel)
		return false;

	m_pNode = GetSceneGraph()->CreateNode(pModel);
	if (!m_pNode)
		return false;
	
	m_pNode->SetWorldTransform(_mWorld);
	GetSceneGraph()->AddNode(m_pNode);

	return true;
}


// Update actor.
void COGActor::Update (int _ElapsedTime)
{
	m_pNode->Update(_ElapsedTime);
}


// Get actor type.
OGActorType COGActor::GetType () const
{
	return m_Type;
}
