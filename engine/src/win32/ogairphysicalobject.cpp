/*
 *  OGAirPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
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
	m_vMove += Vec3(0, -5, 0) * (m_pParams->fAcceleration);
    float fSpeed = m_vMove.length();
	if (fSpeed > m_pParams->fMaxSpeed)
    {
        m_vMove.normalize();
        m_vMove *= m_pParams->fMaxSpeed;
    }

	m_bUpdated = false;
}
