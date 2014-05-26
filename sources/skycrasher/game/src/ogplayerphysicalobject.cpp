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
#include "ogplayerphysicalobject.h"


COGPlayerPhysicalObject::COGPlayerPhysicalObject ()
{
	m_pPhysics = GetPhysics();
}


COGPlayerPhysicalObject::~COGPlayerPhysicalObject ()
{
}


// create object
void COGPlayerPhysicalObject::Create (const IOGAabb& _Aabb, 
                                      IOGPhysicalParams* _pParams,
                                      void* _pParentActor)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_PLAYER;
	m_Aabb = _Aabb;
    m_pActor = (IOGActor*)_pParentActor;
    m_Obb.Create(m_Aabb);
}


// Update transforms.
void COGPlayerPhysicalObject::Update (unsigned long _ElapsedTime)
{
    COGPhysicalObject::Update(_ElapsedTime);
    	
	m_bUpdated = false;
}


// Bound object position to be in level space.
bool COGPlayerPhysicalObject::BoundPosition ()
{
	OGVec3 vLeftBorder, vRightBorder;
	m_pPhysics->GetBordersAtPoint(m_vPosition, vLeftBorder, vRightBorder);
	OG_CLAMP(m_vPosition.x, vLeftBorder.x, vRightBorder.x);
	return true;
}


// Stabilize rotation.
bool COGPlayerPhysicalObject::StabilizeRotation ()
{
    m_vRotation.z /= 1.08f;
    m_vRotation.x /= 1.08f;

	return true;
}
