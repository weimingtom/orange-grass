/*
 *  OGMissilePhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogmissilephysicalobject.h"


COGMissilePhysicalObject::COGMissilePhysicalObject ()
{
}


COGMissilePhysicalObject::~COGMissilePhysicalObject ()
{
}


// create object
void COGMissilePhysicalObject::Create (const IOGAabb& _Aabb, 
                                       IOGPhysicalParams* _pParams,
                                       void* _pParentActor)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_MISSILE;
	m_Aabb = _Aabb;
    m_pActor = (IOGActor*)_pParentActor;
    m_Obb.Create(m_Aabb);
}


// check collision.
bool COGMissilePhysicalObject::CheckCollision (IOGPhysicalObject* _pObject)
{
    if (!m_pListener)
        return false;

	if (!m_bActive)
		return false;

    if (m_vPrevPosition == m_vPosition)
        return false;

	const IOGObb& obb = _pObject->GetOBB();
    //if (obb.CheckLineIntersection(m_vPrevPosition, m_vPosition))
    if (Dist3D(m_vPosition, obb.m_vCenter) <= obb.m_Aabb.GetRadius())
    {
        IOGCollision collision;
        collision.pActorMissile = m_pActor;
		collision.pActorBot = _pObject->GetActor();
        if (_pObject->RespondOnCollision(collision))
        {
			return m_pListener->OnCollision(collision);
        }
    }
    return false;
}


// Update directions.
void COGMissilePhysicalObject::UpdateDirections ()
{
	MatrixVec3Multiply(m_vLook, Vec3(0,0,-1), m_mWorld);
	m_vLook.normalize();
	MatrixVec3Multiply(m_vRight, Vec3(1,0,0), m_mWorld);
	m_vRight.normalize();
	MatrixVec3Multiply(m_vUp, Vec3(0,1,0), m_mWorld);
	m_vUp.normalize();
}
