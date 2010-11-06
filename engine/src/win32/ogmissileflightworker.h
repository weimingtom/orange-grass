/*
 *  OGMissileFlightWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMISSILEFLIGHTWORKER_H_
#define OGMISSILEFLIGHTWORKER_H_

#include "ogworker.h"


class COGMissileFlightWorker : public COGWorker
{
public:
	COGMissileFlightWorker();
	virtual ~COGMissileFlightWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state.
	virtual void Activate (bool _bActive);

	// Set target.
	virtual void SetTarget (const Vec3& _vTarget);

	// Set target.
	virtual void SetTarget (IOGActor* _pTarget);

	// Reset worker.
	virtual void Reset ();

protected:

	// Update actor.
	virtual void UpdateStraight (unsigned long _ElapsedTime);

	// Update actor.
	virtual void UpdateTargeted (unsigned long _ElapsedTime);

protected:

    enum FlightStatus
    {
        WRK_STATUS_LAUNCH,
        WRK_STATUS_TARGETING,
        WRK_STATUS_STRAIGHT
    };

    Vec3		m_vStartPos;

    Vec3        m_vTarget;
    IOGActor*   m_pTarget;
    bool        m_bTargeted;
    float       m_fFlightDistance;

    FlightStatus    m_FlightStatus;
    float           m_fPrevDistToTarget;
};


#endif
