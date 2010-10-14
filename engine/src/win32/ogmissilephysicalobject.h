/*
 *  OGMissilePhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
};

#endif
