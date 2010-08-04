/*
 *  IOGPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGPHYSICALOBJECT_H_
#define IOGPHYSICALOBJECT_H_

#include "IOGMath.h"


enum OGPhysicsType
{
	OG_PHYSICS_NONE = -1,
	OG_PHYSICS_STATIC
};


class IOGPhysicalObject
{
public:
	// destructor
	virtual ~IOGPhysicalObject () {}

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const = 0;

	// set world transform.
	virtual void SetWorldTransform (
		const Vec3& _vPos, 
		const Vec3& _vRot, 
		const Vec3& _vScale) = 0;

	// get position.
	virtual const Vec3& GetPosition () const = 0;

	// get rotation.
	virtual const Vec3& GetRotation () const = 0;

	// get scaling.
	virtual const Vec3& GetScaling () const = 0;

	// set position.
	virtual void SetPosition (const Vec3& _vPos) = 0;

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot) = 0;

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale) = 0;

	// get physics type.
	virtual OGPhysicsType GetPhysicsType () const = 0;

	// Update transforms.
	virtual void Update (int _ElapsedTime) = 0;
};

#endif
