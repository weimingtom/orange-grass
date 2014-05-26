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
	virtual void SetTarget (const OGVec3& _vTarget);

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

    OGVec3		m_vStartPos;

    OGVec3        m_vTarget;
    IOGActor*   m_pTarget;
    bool        m_bTargeted;

    FlightStatus    m_FlightStatus;
    float           m_fPrevDistToTarget;
	unsigned long	m_FlightTime;
};


#endif
