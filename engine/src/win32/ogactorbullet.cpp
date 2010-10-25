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
}


COGActorBullet::~COGActorBullet()
{
    m_pOwner = NULL;
}


// Set owner.
void COGActorBullet::SetOwner (IOGActor* _pOwner, const Vec3& _vLaunchOffset)
{
    m_pOwner = _pOwner;
    m_vLaunchOffset = _vLaunchOffset;
}


// Fire to target.
void COGActorBullet::Fire (const Vec3& _vTarget)
{
}
