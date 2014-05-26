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
#include "ogairphysicalobject.h"


COGAirPhysicalObject::COGAirPhysicalObject ()
{
}


COGAirPhysicalObject::~COGAirPhysicalObject ()
{
}


// create object
void COGAirPhysicalObject::Create (const IOGAabb& _Aabb, 
                                   IOGPhysicalParams* _pParams,
                                   void* _pParentActor)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_AIRBOT;
	m_Aabb = _Aabb;
    m_pActor = (IOGActor*)_pParentActor;
    m_Obb.Create(m_Aabb);
}


// fall.
void COGAirPhysicalObject::Fall ()
{
	m_vAcceleration += OGVec3(0, -1, 0) * m_pParams->fAcceleration;
    float fSpeed = m_vAcceleration.length();
	if (fSpeed > m_pParams->fMaxSpeed)
    {
        m_vAcceleration.normalize();
        m_vAcceleration *= m_pParams->fMaxSpeed;
    }

	m_bUpdated = false;
}
