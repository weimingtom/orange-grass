/*
 *  OGBotFlightWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGBOTFLIGHTWORKER_H_
#define OGBOTFLIGHTWORKER_H_

#include "ogworker.h"


class COGBotFlightWorker : public COGWorker
{
public:
	COGBotFlightWorker();
	virtual ~COGBotFlightWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state.
	virtual void Activate (bool _bActive);

	// Reset worker.
	virtual void Reset ();

protected:

    OGVec3		m_vStartPos;
};


#endif
