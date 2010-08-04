/*
 *  IOGStaticPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSTATICPHYSICALOBJECT_H_
#define OGSTATICPHYSICALOBJECT_H_

#include "OGPhysicalObject.h"


class COGStaticPhysicalObject : public COGPhysicalObject
{
public:
	COGStaticPhysicalObject ();
	virtual ~COGStaticPhysicalObject ();

	// create object
	virtual void Create (const IOGAabb& _Aabb);
};

#endif
