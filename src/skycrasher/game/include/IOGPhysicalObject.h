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
#include "IOGCollisionListener.h"


class IOGPhysicalObject
{
public:
	// destructor
	virtual ~IOGPhysicalObject () {}

	// create object
	virtual void Create (const IOGAabb& _Aabb, IOGPhysicalParams* _pParams, void* _pParentActor) = 0;

    // add collision handler.
    virtual void AddCollisionListener (IOGCollisionListener* _pListener) = 0;

    // check collision.
    virtual bool CheckCollision (IOGPhysicalObject* _pObject) = 0;

    // respond on a collision.
    virtual bool RespondOnCollision (const IOGCollision& _Collision) = 0;

	// Set active state.
	virtual void Activate (bool _bActive) = 0;

	// get world transform.
	virtual const OGMatrix& GetWorldTransform () const = 0;

	// set world transform.
	virtual void SetWorldTransform (
		const OGVec3& _vPos, 
		const OGVec3& _vRot, 
		const OGVec3& _vScale) = 0;

	// get position.
	virtual const OGVec3& GetPosition () const = 0;

	// get rotation.
	virtual const OGVec3& GetRotation () const = 0;

	// get scaling.
	virtual const OGVec3& GetScaling () const = 0;

	// get direction.
	virtual const OGVec3& GetDirection () const = 0;

	// set position.
	virtual void SetPosition (const OGVec3& _vPos) = 0;

	// set rotation.
	virtual void SetRotation (const OGVec3& _vRot) = 0;

	// set scaling.
	virtual void SetScaling (const OGVec3& _vScale) = 0;

	// strafe.
	virtual void Strafe (float _fDir) = 0;

	// accelerate.
	virtual void Accelerate (float _fDir) = 0;

	// move.
	virtual void Move (const OGVec3& _vDir) = 0;

	// fall.
	virtual void Fall () = 0;

	// orient on point.
	virtual bool Orient (const OGVec3& _vPoint) = 0;

	// strabilize object.
	virtual bool Stabilize () = 0;

	// get physics type.
	virtual OGPhysicsType GetPhysicsType () const = 0;

	// get actor.
	virtual void* GetActor () = 0;

	// get OBB.
	virtual const IOGObb& GetOBB () const = 0;

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime) = 0;
};

#endif
