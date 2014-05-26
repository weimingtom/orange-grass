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
