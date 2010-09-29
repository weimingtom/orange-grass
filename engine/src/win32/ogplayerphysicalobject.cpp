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
    m_fRolling = 0.0f;
	m_pPhysics = GetPhysics();
}


COGPlayerPhysicalObject::~COGPlayerPhysicalObject ()
{
}


// create object
void COGPlayerPhysicalObject::Create (const IOGAabb& _Aabb, IOGPhysicalParams* _pParams)
{
    m_pParams = _pParams;
	m_Type = OG_PHYSICS_PLAYER;
	m_Aabb = _Aabb;
    m_Obb.Create(m_Aabb);
    m_vStrafeVec = Vec3(0,0,0);
}


// strafe.
void COGPlayerPhysicalObject::Strafe (float _fDir)
{
    m_vStrafeVec += Vec3(_fDir,0,0);
    m_fRolling += _fDir;
	m_bUpdated = false;
}


// Update transforms.
void COGPlayerPhysicalObject::Update (unsigned long _ElapsedTime)
{
    m_vPosition += Vec3(0,0,-1.0f) * (m_pParams->fMaxSpeed * _ElapsedTime);

    Vec3 vLeftBorder, vRightBorder;
    m_pPhysics->GetBordersAtPoint(m_vPosition, vLeftBorder, vRightBorder);
    Vec3 vStrafeDist = m_vStrafeVec * (m_pParams->fStrafeMaxSpeed * _ElapsedTime);
    m_vPosition += vStrafeDist;
    OG_CLAMP(m_vPosition.x, vLeftBorder.x, vRightBorder.x);

    m_vRotation.z += m_fRolling * m_pParams->fRollSpeed * _ElapsedTime;
    OG_CLAMP(m_vRotation.z, -m_pParams->fMaxRollAngle, m_pParams->fMaxRollAngle);

    COGPhysicalObject::Update(_ElapsedTime);

    m_vStrafeVec.x /= 1.08f;
    m_fRolling /= 1.08f;
    m_vRotation.z /= 1.08f;
    
    m_vPrevPosition = m_vPosition;
	
	m_bUpdated = false;
}
