/*
 *  OGFinishLevelWorker.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGFINISHLEVELWORKER_H_
#define OGFINISHLEVELWORKER_H_

#include "ogworker.h"
#include "ogorientworker.h"


class COGFinishLevelWorker : public COGWorker
{
public:
	COGFinishLevelWorker();
	virtual ~COGFinishLevelWorker();

	// Create worker.
	virtual bool Create(IOGActor* _pActor);

	// Update worker.
	virtual void Update (unsigned long _ElapsedTime);

	// Set target.
    void SetTarget(const OGVec3& _vTarget);

	// Set active state.
	virtual void Activate (bool _bActive);

	// Reset worker.
	virtual void Reset ();

protected:

    enum FinishLevelWorkerState
    {
        FINISHWRK_STATE_MOVING,
        FINISHWRK_STATE_LANDING
    };

    OGVec3 m_vTarget;
    COGOrientWorker m_OrientWorker;
    FinishLevelWorkerState m_WrkState;
};


#endif
