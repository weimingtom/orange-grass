/*
 *  OGBonusPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGBONUSPHYSICALOBJECT_H_
#define OGBONUSPHYSICALOBJECT_H_

#include "ogphysicalobject.h"


class COGBonusPhysicalObject : public COGPhysicalObject
{
public:
	COGBonusPhysicalObject ();
	virtual ~COGBonusPhysicalObject ();

	// create object
	virtual void Create (
        const IOGAabb& _Aabb, 
        IOGPhysicalParams* _pParams, 
        void* _pParentActor);
};

#endif
