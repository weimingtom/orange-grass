/*
 *  OGOrientWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGORIENTWORKER_H_
#define OGORIENTWORKER_H_

#include "ogworker.h"


class COGOrientWorker : public COGWorker
{
public:
	COGOrientWorker();
	virtual ~COGOrientWorker();

	// Set target.
    virtual void SetTarget(const OGVec3& _vTarget) {m_vTarget = _vTarget;}

	// Update worker.
	virtual void Update (unsigned long _ElapsedTime);

protected:

    OGVec3		m_vTarget;
};


#endif
