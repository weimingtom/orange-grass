/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "Game.h"
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
