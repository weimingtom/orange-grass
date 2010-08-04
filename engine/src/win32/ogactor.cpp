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


COGActor::COGActor() :	m_pNode(NULL),
						m_Type(OG_ACTOR_NONE),
                        m_pPhysicalObject(NULL),
                        m_bAdded(false),
                        m_pModel(NULL)
{
}


COGActor::COGActor(OGActorType _Type) : m_pNode(NULL),
										m_Type(_Type),
                                        m_pPhysicalObject(NULL),
                                        m_bAdded(false),
                                        m_pModel(NULL)
{
}


COGActor::~COGActor()
{
	if (m_pNode)
	{
        if (m_bAdded)
		    GetSceneGraph()->RemoveNode(m_pNode);
        else
            OG_SAFE_DELETE(m_pNode);
		m_pNode = NULL;
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
bool COGActor::Create (const char* _pModelAlias,
					   const Vec3& _vPos,
					   const Vec3& _vRot,
                       const Vec3& _vScale)
{
	if (m_Type == OG_ACTOR_NONE)
		return false;

	m_pModel = GetResourceMgr()->GetModel(_pModelAlias);
	if (!m_pModel)
		return false;

	m_pNode = GetSceneGraph()->CreateNode(m_pModel);
	if (!m_pNode)
		return false;
	
    m_pPhysicalObject = GetPhysics()->CreateObject(OG_PHYSICS_STATIC, m_pModel->GetAABB());
    if (!m_pPhysicalObject)
        return false;

	m_pPhysicalObject->SetWorldTransform(_vPos, _vRot, _vScale);
	return true;
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
const char* COGActor::GetAlias () const
{
    return m_pModel->GetAlias();
}


// Check actor's OBB intersection with ray.
bool COGActor::CheckIntersection (const Vec3& _vRayStart,
                                  const Vec3& _vRayDir ) const
{
    return m_pPhysicalObject->GetOBB().CheckIntersection (_vRayStart, _vRayDir);
}
