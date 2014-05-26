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
#ifndef OGPLAYERPHYSICALOBJECT_H_
#define OGPLAYERPHYSICALOBJECT_H_

#include "ogphysicalobject.h"


class COGPlayerPhysicalObject : public COGPhysicalObject
{
public:
	COGPlayerPhysicalObject ();
	virtual ~COGPlayerPhysicalObject ();

	// create object
	virtual void Create (
        const IOGAabb& _Aabb, 
        IOGPhysicalParams* _pParams,
        void* _pParentActor);

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime);

protected:

	// Bound object position to be in level space.
	virtual bool BoundPosition ();

	// Stabilize rotation.
	virtual bool StabilizeRotation ();

protected:

	IOGPhysics*	m_pPhysics;
};

#endif
