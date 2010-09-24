/*
 *  IOGStaticPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogstaticphysicalobject.h"


COGStaticPhysicalObject::COGStaticPhysicalObject () : COGPhysicalObject()
{
}


COGStaticPhysicalObject::~COGStaticPhysicalObject ()
{
}


// create object
void COGStaticPhysicalObject::Create (const IOGAabb& _Aabb, IOGPhysicalParams* _pParams)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_STATIC;
	m_Aabb = _Aabb;
    m_Obb.Create(m_Aabb);
}
