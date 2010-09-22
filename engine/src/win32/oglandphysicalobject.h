/*
 *  IOGLandPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLANDPHYSICALOBJECT_H_
#define OGLANDPHYSICALOBJECT_H_

#include "ogphysicalobject.h"


class COGLandPhysicalObject : public COGPhysicalObject
{
public:
	COGLandPhysicalObject ();
	virtual ~COGLandPhysicalObject ();

	// create object
	virtual void Create (const IOGAabb& _Aabb, const IOGPhysicalParams& _Params);
};

#endif
