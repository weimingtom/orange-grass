/*
 *  OGMissileFlightWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMISSILEFLIGHTWORKER_H_
#define OGMISSILEFLIGHTWORKER_H_

#include "ogworker.h"


class COGMissileFlightWorker : public COGWorker
{
public:
	COGMissileFlightWorker();
	virtual ~COGMissileFlightWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state.
	virtual void Activate (bool _bActive);

	// Reset worker.
	virtual void Reset ();

protected:

    Vec3		m_vStartPos;
};


#endif
