/*
 *  ogmissileflightworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogmissileflightworker.h"
#include "IOGMath.h"
#include <float.h>


COGMissileFlightWorker::COGMissileFlightWorker()
{
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
    m_fFlightDistance = 150.0f;
	return true;
}


// Set target.
void COGMissileFlightWorker::SetTarget (const Vec3& _vTarget)
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
}


// Reset worker.
void COGMissileFlightWorker::Reset ()
{
	COGWorker::Reset();
    m_bTargeted = false;
    m_pTarget = NULL;
    m_FlightStatus = WRK_STATUS_LAUNCH;
    m_fPrevDistToTarget = FLT_MAX;
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
}


// Update actor.
void COGMissileFlightWorker::UpdateStraight (unsigned long _ElapsedTime)
{
	Vec3 vCurPos = m_pActor->GetPhysicalObject()->GetPosition();
	float fDist = Dist2D(vCurPos, m_vStartPos);

    if (fDist > m_fFlightDistance)
    {
        Activate(false);
        m_bFinished = true;
    }
    else
    {
        m_pActor->GetPhysicalObject()->Accelerate(1.0f);
    }
}


// Update actor.
void COGMissileFlightWorker::UpdateTargeted (unsigned long _ElapsedTime)
{
	Vec3 vCurPos = m_pActor->GetPhysicalObject()->GetPosition();
	float fDist = Dist2D(vCurPos, m_vStartPos);

    Vec3 vTarget = m_pTarget ? m_pTarget->GetPhysicalObject()->GetPosition() : m_vTarget;

	float fDistToTarget = Dist2D(vCurPos, vTarget);
    if (fDistToTarget > m_fPrevDistToTarget)
    {
        m_FlightStatus = WRK_STATUS_STRAIGHT;
    }
    m_fPrevDistToTarget = fDistToTarget;

    if (fDist > m_fFlightDistance)
    {
        Activate(false);
        m_bFinished = true;
    }
    else if (fDist > 10 && fDist <= m_fFlightDistance)
    {
        if (m_FlightStatus == WRK_STATUS_LAUNCH)
        {
            m_FlightStatus = WRK_STATUS_TARGETING;
        }
        if (m_FlightStatus == WRK_STATUS_TARGETING)
        {
            m_pActor->GetPhysicalObject()->Orient(vTarget);
            m_pActor->GetPhysicalObject()->Accelerate(1.0f);
        }
    }

    if (m_FlightStatus == WRK_STATUS_LAUNCH || m_FlightStatus == WRK_STATUS_STRAIGHT)
    {
        m_pActor->GetPhysicalObject()->Accelerate(1.0f);
    }
}
