/*
 *  ogbotfallingworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogbotfallingworker.h"


COGBotFallingWorker::COGBotFallingWorker()
{
}


COGBotFallingWorker::~COGBotFallingWorker()
{
}


// Create worker.
bool COGBotFallingWorker::Create(IOGActor* _pActor)
{
	COGWorker::Create(_pActor);
	return true;
}


// Update actor.
void COGBotFallingWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

	OGVec3 vCurPos = m_pActor->GetPhysicalObject()->GetPosition();
	if (vCurPos.y <= 10.0f)
	{
		Activate(false);
		m_bFinished = true;
	}
	else
	{
	    m_pActor->GetPhysicalObject()->Accelerate(1.0f);
		m_pActor->GetPhysicalObject()->Fall();
	}
}


// Set active state.
void COGBotFallingWorker::Activate (bool _bActive)
{
	COGWorker::Activate(_bActive);
}


// Reset worker.
void COGBotFallingWorker::Reset ()
{
	COGWorker::Reset();
}
