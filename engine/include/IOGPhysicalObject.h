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

#include "IOGPhysicalParams.h"


class IOGPhysicalObject
{
public:
	// destructor
	virtual ~IOGPhysicalObject () {}

	// create object
	virtual void Create (const IOGAabb& _Aabb, IOGPhysicalParams* _pParams) = 0;

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

	// get direction.
	virtual const Vec3& GetDirection () const = 0;

	// set position.
	virtual void SetPosition (const Vec3& _vPos) = 0;

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot) = 0;

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale) = 0;

	// strafe.
	virtual void Strafe (float _fDir) = 0;

	// accelerate.
	virtual void Accelerate (float _fDir) = 0;

	// orient on point.
	virtual bool Orient (const Vec3& _vPoint) = 0;

	// strabilize object.
	virtual bool Stabilize () = 0;

	// get physics type.
	virtual OGPhysicsType GetPhysicsType () const = 0;

	// get OBB.
	virtual const IOGObb& GetOBB () const = 0;

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime) = 0;
};

#endif
