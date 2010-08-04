/*
 *  OGPhysics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPHYSICS_H_
#define OGPHYSICS_H_

#include "IOGPhysics.h"
#include <vector>


class COGPhysics : public IOGPhysics
{
public:
	COGPhysics ();
	virtual ~COGPhysics ();

	// Create object
	virtual IOGPhysicalObject* CreateObject (
		OGPhysicsType _Type,
		const IOGAabb& _Aabb );

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject);

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject);

	// Update transforms.
	virtual void Update (int _ElapsedTime);

private:

	std::vector<IOGPhysicalObject*>	m_ObjList;
};

#endif
