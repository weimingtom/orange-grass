/*
 *  ogworker.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
