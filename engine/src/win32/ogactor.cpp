/*
 *  ogactor.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactor.h"


COGActor::COGActor() :	m_bActive(true),
						m_bAdded(false),
						m_pParams(NULL),
                        m_pNode(NULL),
                        m_pPhysicalObject(NULL),
                        m_pModel(NULL),
						m_Status(OG_ACTORSTATUS_ALIVE)
{
}


COGActor::~COGActor()
{
}


// Adding to actor manager event handler.
void COGActor::OnAddedToManager ()
{
    GetPhysics()->AddObject(m_pPhysicalObject);
	GetSceneGraph()->AddNode(m_pNode);
    m_bAdded = true;
}


// Update actor.
void COGActor::Update (unsigned long _ElapsedTime)
{
	switch (m_Status)
	{
	case OG_ACTORSTATUS_ALIVE:
		UpdateAlive(_ElapsedTime);
		break;

	case OG_ACTORSTATUS_FALLING:
		UpdateFalling(_ElapsedTime);
		break;

	default:
		break;
	}
}


// Update alive actor.
void COGActor::UpdateAlive (unsigned long _ElapsedTime)
{
    m_pNode->Update(_ElapsedTime);
}


// Update falling actor.
void COGActor::UpdateFalling (unsigned long _ElapsedTime)
{
}


// Update actors in editor.
void COGActor::UpdateEditor (unsigned long _ElapsedTime)
{
    m_pNode->Update(_ElapsedTime);
}


// Get actor type.
OGActorType COGActor::GetType () const
{
	return m_pParams->type;
}


// Get scene graph node.
IOGSgNode* COGActor::GetSgNode ()
{
    return m_pNode;
}


// Get physical object.
IOGPhysicalObject* COGActor::GetPhysicalObject ()
{
    return m_pPhysicalObject;
}


// Get model alias
const std::string& COGActor::GetAlias () const
{
	return m_pParams->alias;
}


// Set active state
void COGActor::Activate (bool _bActive)
{
	if (_bActive == m_bActive || m_Status == OG_ACTORSTATUS_DEAD)
		return;

	m_bActive = _bActive;
	m_pPhysicalObject->Activate(m_bActive);
	m_pNode->Activate(m_bActive);
}


// Check actor's OBB intersection with ray.
bool COGActor::CheckIntersection (const Vec3& _vRayStart,
                                  const Vec3& _vRayDir ) const
{
    return m_pPhysicalObject->GetOBB().CheckIntersection (_vRayStart, _vRayDir);
}


// collision event handler
bool COGActor::OnCollision (const IOGCollision& _Collision)
{
    return false;
}
