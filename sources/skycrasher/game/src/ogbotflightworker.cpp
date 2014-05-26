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
