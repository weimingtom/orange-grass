/*
 *  IOGPhysics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
		OGPhysicsType _Type,
		const IOGAabb& _Aabb ) = 0;

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject) = 0;

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject) = 0;

	// Update transforms.
	virtual void Update (int _ElapsedTime) = 0;
};

#endif
