/*
 *  ogbotflightworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogbotflightworker.h"


COGBotFlightWorker::COGBotFlightWorker()
{
}


COGBotFlightWorker::~COGBotFlightWorker()
{
}


// Create worker.
bool COGBotFlightWorker::Create(IOGActor* _pActor)
{
	COGWorker::Create(_pActor);
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
	return true;
}


// Update actor.
void COGBotFlightWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

    m_pActor->GetPhysicalObject()->Accelerate(1.0f);
}


// Set active state.
void COGBotFlightWorker::Activate (bool _bActive)
{
	COGWorker::Activate(_bActive);
}


// Reset worker.
void COGBotFlightWorker::Reset ()
{
	COGWorker::Reset();
	m_vStartPos = m_pActor->GetPhysicalObject()->GetPosition();
}
