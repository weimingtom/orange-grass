/*
 *  ogorientworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogorientworker.h"


COGOrientWorker::COGOrientWorker()
{
}


COGOrientWorker::~COGOrientWorker()
{
}


// Update worker.
void COGOrientWorker::Update (unsigned long _ElapsedTime)
{
	if (!m_bActive)
		return;

    bool bDone = m_pActor->GetPhysicalObject()->Orient(m_vTarget);
	if (bDone)
	{
		Activate(false);
		m_bFinished = true;
	}
	else
	{
	}
}
