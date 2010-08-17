/*
 *  OGPlayerPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogplayerphysicalobject.h"


COGPlayerPhysicalObject::COGPlayerPhysicalObject () : COGPhysicalObject()
{
}


COGPlayerPhysicalObject::~COGPlayerPhysicalObject ()
{
}


// create object
void COGPlayerPhysicalObject::Create (const IOGAabb& _Aabb)
{
	m_Type = OG_PHYSICS_AIRBOT;
	m_Aabb = _Aabb;
    m_Obb.Create(m_Aabb);
}


// Update transforms.
void COGPlayerPhysicalObject::Update (unsigned long _ElapsedTime)
{
    m_vPosition += Vec3(0,0,-1.0f) * (0.02f * _ElapsedTime);
    COGPhysicalObject::Update(_ElapsedTime);
}
