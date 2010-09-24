/*
 *  OGWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGWORKER_H_
#define OGWORKER_H_

#include "IOGActor.h"


class COGWorker
{
public:
	COGWorker();
	virtual ~COGWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Get active state.
	virtual bool IsActive () const { return m_bActive; }

	// Get finished state.
	virtual bool IsFinished () const { return m_bFinished; }

	// Set active state.
	virtual void Activate (bool _bActive);

	// Reset worker.
	virtual void Reset ();

protected:

    bool		m_bActive;
    bool		m_bFinished;
	IOGActor*	m_pActor;
};


#endif
