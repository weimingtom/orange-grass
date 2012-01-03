/*
 *  ogstabilizeworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "Game.h"
#include "ogstabilizeworker.h"


COGStabilizeWorker::COGStabilizeWorker()
{
}


COGStabilizeWorker::~COGStabilizeWorker()
{
}


// Update worker.
void COGStabilizeWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

    bool bDone = m_pActor->GetPhysicalObject()->Stabilize();
	if (bDone)
	{
		Activate(false);
		m_bFinished = true;
	}
	else
	{
	}
}
