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

#include "OGActor.h"
#include "ogmissileflightworker.h"


class COGActorMissile : public COGActor
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

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state
	virtual void Activate (bool _bActive);

	// Set owner.
	virtual void SetOwner (IOGActor* _pOwner, const Vec3& _vLaunchOffset);

	// Fire to target.
	virtual void Fire (const Vec3& _vTarget);

protected:

    IOGEffect*  m_pHeadEffect;
    IOGActor*   m_pOwner;
    Vec3        m_vLaunchOffset;
	COGMissileFlightWorker	m_FlightWorker;
};


#endif
