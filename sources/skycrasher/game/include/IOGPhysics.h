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
#ifndef IOGPHYSICS_H_
#define IOGPHYSICS_H_

#include "IOGPhysicalObject.h"


class IOGPhysics
{
public:
	// destructor
	virtual ~IOGPhysics () {}

	// Clear scene graph
	virtual void Clear () = 0;

	// Create object
	virtual IOGPhysicalObject* CreateObject (
		IOGPhysicalParams* _pParams,
		const IOGAabb& _Aabb,
        void* _pActor) = 0;

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject) = 0;

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject) = 0;

    // Set level borders
    virtual void SetLevelBorders (const OGVec3& _vStart, const OGVec3& _vFinish, float _fWidth) = 0;

    // Get borders at point
    virtual void GetBordersAtPoint (const OGVec3& _vPos, OGVec3& _vLeft, OGVec3& _vRight) = 0;

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update transforms for the whole scene.
	virtual void UpdateAll (unsigned long _ElapsedTime) = 0;
};

#endif
