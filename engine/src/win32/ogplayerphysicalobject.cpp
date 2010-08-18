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
    m_vStrafeVec = Vec3(0,0,0);
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
    m_vStrafeVec = Vec3(0,0,0);
}


// strafe.
void COGPlayerPhysicalObject::Strafe (float _fDir)
{
    m_vStrafeVec += Vec3(_fDir,0,0);
}


// Update transforms.
void COGPlayerPhysicalObject::Update (unsigned long _ElapsedTime)
{
    m_vPosition += Vec3(0,0,-1.0f) * (0.02f * _ElapsedTime);
    COGPhysicalObject::Update(_ElapsedTime);
}
