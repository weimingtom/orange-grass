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


class COGPhysicalObject : public IOGPhysicalObject
{
public:
	COGPhysicalObject ();	
	virtual ~COGPhysicalObject ();

	// create object
	virtual void Create (const IOGAabb& _Aabb) = 0;

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

	// set position.
	virtual void SetPosition (const Vec3& _vPos);

	// set rotation.
	virtual void SetRotation (const Vec3& _vRot);

	// set scaling.
	virtual void SetScaling (const Vec3& _vScale);

	// strafe.
	virtual void Strafe (float _fDir);

	// get physics type.
	virtual OGPhysicsType GetPhysicsType () const;

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
	IOGAabb			m_Aabb;
	IOGObb			m_Obb;
};

#endif
