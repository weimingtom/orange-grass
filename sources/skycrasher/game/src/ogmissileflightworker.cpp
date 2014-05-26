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
#include "ogmissileflightworker.h"
#include "IOGMath.h"
#include <float.h>

static const unsigned int MaxFlightTime		= 5000;
static const unsigned int MaxLaunchingTime	= 200;


COGMissileFlightWorker::COGMissileFlightWorker()
{
	m_FlightTime = 0;
    m_bTargeted = false;
    m_pTarget = NULL;
}


COGMissileFlightWorker::~COGMissileFlightWorker()
{
}


// Create worker.
bool COGMissileFlightWorker::Create(IOGActor* _pActor)
{
	COGWorker::Create(_pActor);
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
	m_FlightTime = 0;
	return true;
}


// Set target.
void COGMissileFlightWorker::SetTarget (const OGVec3& _vTarget)
{
    m_vTarget = _vTarget;
    m_bTargeted = true;
}


// Set target.
void COGMissileFlightWorker::SetTarget (IOGActor* _pTarget)
{
    m_pTarget = _pTarget;
    m_bTargeted = true;
}


// Update actor.
void COGMissileFlightWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

	m_FlightTime += _ElapsedTime;
	if (m_FlightTime >= MaxFlightTime)
	{
        Activate(false);
        m_bFinished = true;
		return;
	}

    if (m_bTargeted)
    {
        UpdateTargeted(_ElapsedTime);
    }
    else
    {
        UpdateStraight(_ElapsedTime);
    }
}


// Set active state.
void COGMissileFlightWorker::Activate (bool _bActive)
{
	COGWorker::Activate(_bActive);
	m_FlightTime = 0;
}


// Reset worker.
void COGMissileFlightWorker::Reset ()
{
	COGWorker::Reset();
	m_FlightTime = 0;
    m_bTargeted = false;
    m_pTarget = NULL;
    m_FlightStatus = WRK_STATUS_LAUNCH;
    m_fPrevDistToTarget = FLT_MAX;
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
}


// Update actor.
void COGMissileFlightWorker::UpdateStraight (unsigned long _ElapsedTime)
{
	m_pActor->GetPhysicalObject()->Accelerate(1.0f);
}


// Update actor.
void COGMissileFlightWorker::UpdateTargeted (unsigned long _ElapsedTime)
{
	switch(m_FlightStatus)
	{
	case WRK_STATUS_LAUNCH:
		{
			m_pActor->GetPhysicalObject()->Accelerate(1.0f);
			if (m_FlightTime >= MaxLaunchingTime)
			{
				m_FlightStatus = WRK_STATUS_TARGETING;
			}
		}
		break;

	case WRK_STATUS_TARGETING:
		{
			OGVec3 vTargetPos = m_pTarget ? m_pTarget->GetPhysicalObject()->GetPosition() : m_vTarget;

			m_pActor->GetPhysicalObject()->Orient(vTargetPos);
			m_pActor->GetPhysicalObject()->Accelerate(1.0f);

			OGVec3 vCurPos = m_pActor->GetPhysicalObject()->GetPosition();
			float fDistToTarget = Dist2D(vCurPos, vTargetPos);
			if (fDistToTarget > m_fPrevDistToTarget)
			{
				m_FlightStatus = WRK_STATUS_STRAIGHT;
			}
		    m_fPrevDistToTarget = fDistToTarget;
		}
		break;

	case WRK_STATUS_STRAIGHT:
		{
			m_pActor->GetPhysicalObject()->Accelerate(1.0f);
		}
		break;
	}
}
