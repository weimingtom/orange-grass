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
#ifndef OGACTORBULLET_H_
#define OGACTORBULLET_H_

#include "ogactor.h"


class COGActorBullet : public COGActor
{
public:
	COGActorBullet();
	virtual ~COGActorBullet();

	// Set owner.
	virtual void SetOwner (IOGActor* _pOwner, const OGVec3& _vLaunchOffset);

	// Set target.
	virtual void SetTarget (IOGActor* _pTarget);

	// Set target.
	virtual void SetTarget (const OGVec3& _vTarget);

	// Set damage points.
	virtual void SetDamagePoints (unsigned int _DamagePoints);

	// Fire.
	virtual void Fire ();

protected:

	IOGActor*   m_pOwner;
	IOGActor*   m_pTarget;
	OGVec3		m_vTarget;
    OGVec3        m_vLaunchOffset;
};


#endif
