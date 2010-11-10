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
	Vec3 vLeftBorder, vRightBorder;
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
