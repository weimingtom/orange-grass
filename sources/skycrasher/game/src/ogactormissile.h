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
#ifndef OGACTORMISSILE_H_
#define OGACTORMISSILE_H_

#include "ogactorbullet.h"
#include "ogmissileflightworker.h"


class COGActorMissile : public COGActorBullet
{
public:
	COGActorMissile();
	virtual ~COGActorMissile();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Set active state
	virtual void Activate (bool _bActive);

	// Fire.
	virtual void Fire ();

	// Set target.
	virtual void SetTarget (const OGVec3& _vTarget);

	// Set target.
	virtual void SetTarget (IOGActor* _pTarget);

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

protected:

    IOGEffect*				m_pHeadEffect;
    IOGEffect*				m_pCollisionEffect;
    IOGSgNode*              m_pCollisionEffectNode;
	COGMissileFlightWorker	m_FlightWorker;
};


#endif
