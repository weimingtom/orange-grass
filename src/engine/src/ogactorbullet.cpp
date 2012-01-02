/*
 *  ogactorbullet.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogactorbullet.h"


COGActorBullet::COGActorBullet()
{
    m_pOwner = NULL;
	m_pTarget = NULL;
}


COGActorBullet::~COGActorBullet()
{
    m_pOwner = NULL;
	m_pTarget = NULL;
}


// Set owner.
void COGActorBullet::SetOwner (IOGActor* _pOwner, const OGVec3& _vLaunchOffset)
{
    m_pOwner = _pOwner;

    MatrixVecMultiply(
        m_vLaunchOffset, 
        _vLaunchOffset, 
        m_pOwner->GetPhysicalObject()->GetWorldTransform());
}


// Set target.
void COGActorBullet::SetTarget (IOGActor* _pTarget)
{
	m_pTarget = _pTarget;
}


// Set target.
void COGActorBullet::SetTarget (const OGVec3& _vTarget)
{
	m_vTarget = _vTarget;
}


// Set damage points.
void COGActorBullet::SetDamagePoints (unsigned int _DamagePoints)
{
    m_DamagePoints = _DamagePoints;
}


// Fire.
void COGActorBullet::Fire ()
{
}
