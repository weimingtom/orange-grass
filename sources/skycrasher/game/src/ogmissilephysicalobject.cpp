/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "Game.h"
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
	MatrixVec3Multiply(m_vLook, OGVec3(0,0,-1), m_mWorld);
	m_vLook.normalize();
	MatrixVec3Multiply(m_vRight, OGVec3(1,0,0), m_mWorld);
	m_vRight.normalize();
	MatrixVec3Multiply(m_vUp, OGVec3(0,1,0), m_mWorld);
	m_vUp.normalize();
}
