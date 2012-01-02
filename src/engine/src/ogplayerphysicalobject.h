/*
 *  OGPlayerPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
