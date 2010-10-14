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

    const IOGObb& obb = _pObject->GetOBB();
    if (m_vPrevPosition == m_vPosition)
        return false;
    if (obb.CheckLineIntersection(m_vPrevPosition, m_vPosition))
    {
        IOGCollision collision;
        collision.pActorCollided = NULL;
        if (m_pListener->OnCollision(collision))
        {
            return true;
        }
    }
    return false;
}
