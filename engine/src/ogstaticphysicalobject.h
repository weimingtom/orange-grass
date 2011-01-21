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

#include "ogphysicalobject.h"


class COGStaticPhysicalObject : public COGPhysicalObject
{
public:
	COGStaticPhysicalObject ();
	virtual ~COGStaticPhysicalObject ();

	// create object
	virtual void Create (
        const IOGAabb& _Aabb, 
        IOGPhysicalParams* _pParams,
        void* _pParentActor);

protected:

	// Update directions.
	virtual void UpdateDirections ();
};

#endif
