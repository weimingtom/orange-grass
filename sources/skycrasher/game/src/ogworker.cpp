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
#include "ogworker.h"


COGWorker::COGWorker()
{
	m_pActor = NULL;
	m_bActive = false;
	m_bFinished = false;
}


COGWorker::~COGWorker()
{
}


// Create worker.
bool COGWorker::Create(IOGActor* _pActor)
{
	m_pActor = _pActor;
	return true;
}


// Update actor.
void COGWorker::Update (unsigned long _ElapsedTime)
{
}


// Set active state.
void COGWorker::Activate (bool _bActive)
{
	m_bActive = _bActive;
}


// Reset worker.
void COGWorker::Reset ()
{
	m_bActive = false;
	m_bFinished = false;
}
