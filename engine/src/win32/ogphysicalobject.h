/*
 *  IOGPhysicalObject.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPHYSICALOBJECT_H_
#define OGPHYSICALOBJECT_H_

#include "IOGPhysicalObject.h"
#include "IOGActor.h"


class COGPhysicalObject : public IOGPhysicalObject
{
public:
	COGPhysicalObject ();	
	virtual ~COGPhysicalObject ();

	// create object
	virtual void Create (
        const IOGAabb& _Aabb, 
        IOGPhysicalParams* _pParams, 
        void* _pParentActor) = 0;

    // add collision handler.
    virtual void AddCollisionListener (IOGCollisionListener* _pListener);

    // check collision.
    virtual bool CheckCollision (IOGPhysicalObject* _pObject);

    // respond on a collision.
    virtual bool RespondOnCollision (const IOGCollision& _Collision);

	// Set active state.
	virtual void Activate (bool _bActive);

	// get world transform.
	virtual const MATRIX& GetWorldTransform () const;

	// set world transform.
	virtual void SetWorldTransform (
		const Vec3& _vPos, 
		const Vec3& _vRot, 
		const Vec3& _vScale);

	// get position.
	virtual const Vec3& GetPosition () const;

	// get rotation.
	virtual const Vec3& GetRotation () const;

	// get scaling.
	virtual const Vec3& GetScaling () const;

	// get direction.
	virtual const Vec3& GetDirection () const;

	// set position.
	virtual void SetPosition (const Vec3& _vPos);

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot);

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale);

	// strafe.
	virtual void Strafe (float _fDir);

	// accelerate.
	virtual void Accelerate (float _fDir);

	// orient on point.
	virtual bool Orient (const Vec3& _vPoint);

	// strabilize object.
	virtual bool Stabilize ();

	// get physics type.
	virtual OGPhysicsType GetPhysicsType () const;

	// get actor.
	virtual void* GetActor () {return m_pActor;}

	// get OBB.
	virtual const IOGObb& GetOBB () const;

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime);

protected:

	OGPhysicsType	m_Type;
    MATRIX          m_mWorld;
    Vec3            m_vPosition;
    Vec3            m_vRotation;
    Vec3            m_vScaling;
    Vec3            m_vUp;
    Vec3            m_vLook;
    Vec3            m_vRight;
    Vec3            m_vMove;
    Vec3            m_vTorque;
    Vec3            m_vPrevPosition;
	IOGAabb			m_Aabb;
	IOGObb			m_Obb;
	bool			m_bUpdated;
	bool			m_bActive;
    IOGPhysicalParams*	m_pParams;
    IOGCollisionListener*   m_pListener;
    IOGActor*       m_pActor;
};

#endif
