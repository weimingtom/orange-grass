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
