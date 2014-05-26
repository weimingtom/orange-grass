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
#ifndef OGMISSILEPHYSICALOBJECT_H_
#define OGMISSILEPHYSICALOBJECT_H_

#include "ogphysicalobject.h"


class COGMissilePhysicalObject : public COGPhysicalObject
{
public:
	COGMissilePhysicalObject ();
	virtual ~COGMissilePhysicalObject ();

	// create object
	virtual void Create (
        const IOGAabb& _Aabb, 
        IOGPhysicalParams* _pParams,
        void* _pParentActor);

    // check collision.
    virtual bool CheckCollision (IOGPhysicalObject* _pObject);

protected:

	// Update directions.
	virtual void UpdateDirections ();
};

#endif
