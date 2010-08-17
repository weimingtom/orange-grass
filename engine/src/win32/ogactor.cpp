/*
 *  ogactor.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "orangegrass.h"
#include "ogactor.h"
#include "IOGMath.h"


COGActor::COGActor() :	m_Type(OG_ACTOR_NONE),
                        m_bAdded(false),
                        m_pNode(NULL),
                        m_pPhysicalObject(NULL),
                        m_pModel(NULL)
{
}


COGActor::COGActor(OGActorType _Type) : m_Type(_Type),
                                        m_bAdded(false),
                                        m_pNode(NULL),
                                        m_pPhysicalObject(NULL),
                                        m_pModel(NULL)
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
void COGActor::Update (int _ElapsedTime)
{
    m_pNode->Update(m_pPhysicalObject->GetWorldTransform(), m_pPhysicalObject->GetOBB());
}


// Get actor type.
OGActorType COGActor::GetType () const
{
	return m_Type;
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
    return m_pModel->GetAlias();
}


// Check actor's OBB intersection with ray.
bool COGActor::CheckIntersection (const Vec3& _vRayStart,
                                  const Vec3& _vRayDir ) const
{
    return m_pPhysicalObject->GetOBB().CheckIntersection (_vRayStart, _vRayDir);
}
