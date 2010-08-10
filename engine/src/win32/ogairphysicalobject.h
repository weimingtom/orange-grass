/*
 *  IOGAirPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGAIRPHYSICALOBJECT_H_
#define OGAIRPHYSICALOBJECT_H_

#include "OGPhysicalObject.h"


class COGAirPhysicalObject : public COGPhysicalObject
{
public:
	COGAirPhysicalObject ();
	virtual ~COGAirPhysicalObject ();

	// create object
	virtual void Create (const IOGAabb& _Aabb);
};

#endif
