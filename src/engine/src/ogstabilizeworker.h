/*
 *  OGStabilizeWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSTABILIZEWORKER_H_
#define OGSTABILIZEWORKER_H_

#include "ogworker.h"


class COGStabilizeWorker : public COGWorker
{
public:
	COGStabilizeWorker();
	virtual ~COGStabilizeWorker();

	// Update worker.
	virtual void Update (unsigned long _ElapsedTime);
};


#endif
