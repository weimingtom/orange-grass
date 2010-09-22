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
	virtual void Create (const IOGAabb& _Aabb, const IOGPhysicalParams& _Params);

	// strafe.
	virtual void Strafe (float _fDir);

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime);

protected:

    Vec3    m_vStrafeVec;
    float   m_fRolling;
    Vec3    m_vPrevPosition;
	IOGPhysics*	m_pPhysics;
};

#endif
