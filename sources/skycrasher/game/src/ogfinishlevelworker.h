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
