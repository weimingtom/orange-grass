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


COGMissileFlightWorker::COGMissileFlightWorker()
{
}


COGMissileFlightWorker::~COGMissileFlightWorker()
{
}


// Create worker.
bool COGMissileFlightWorker::Create(IOGActor* _pActor)
{
	COGWorker::Create(_pActor);
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
	return true;
}


// Update actor.
void COGMissileFlightWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

	Vec3 vCurPos = m_pActor->GetPhysicalObject()->GetPosition();
	float fDist = Dist2D(vCurPos, m_vStartPos);
	if (fDist > 300.0f)
	{
		Activate(false);
		m_bFinished = true;
	}
	else
	{
	    m_pActor->GetPhysicalObject()->Accelerate(1.0f);
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
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
}
