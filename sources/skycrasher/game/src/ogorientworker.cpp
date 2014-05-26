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
