/*
 *  OGBotFallingWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGBOTFALLINGWORKER_H_
#define OGBOTFALLINGWORKER_H_

#include "ogworker.h"


class COGBotFallingWorker : public COGWorker
{
public:
	COGBotFallingWorker();
	virtual ~COGBotFallingWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Set active state.
	virtual void Activate (bool _bActive);

	// Reset worker.
	virtual void Reset ();
};


#endif
