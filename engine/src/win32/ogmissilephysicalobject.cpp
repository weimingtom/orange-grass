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


COGMissilePhysicalObject::COGMissilePhysicalObject () : COGPhysicalObject()
{
}


COGMissilePhysicalObject::~COGMissilePhysicalObject ()
{
}


// create object
void COGMissilePhysicalObject::Create (const IOGAabb& _Aabb, IOGPhysicalParams* _pParams)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_MISSILE;
	m_Aabb = _Aabb;
    m_Obb.Create(m_Aabb);
}
