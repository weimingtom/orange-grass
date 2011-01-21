/*
 *  OGActorMissile.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Set active state
	virtual void Activate (bool _bActive);

	// Fire.
	virtual void Fire ();

	// Set target.
	virtual void SetTarget (const Vec3& _vTarget);

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
