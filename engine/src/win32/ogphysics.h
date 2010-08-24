/*
 *  OGPhysics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGPHYSICS_H_
#define OGPHYSICS_H_

#include "IOGPhysics.h"
#include <list>


class COGPhysics : public IOGPhysics
{
public:
	COGPhysics ();
	virtual ~COGPhysics ();

	// Clear scene graph
	virtual void Clear ();

	// Create object
	virtual IOGPhysicalObject* CreateObject (
		OGPhysicsType _Type,
		const IOGAabb& _Aabb );

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject);

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject);

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime);

    // Set level borders
    virtual void SetLevelBorders (const Vec3& _vStart, const Vec3& _vFinish, float _fWidth);

    // Get borders at point
    virtual void GetBordersAtPoint (const Vec3& _vPos, Vec3& _vLeft, Vec3& _vRight);

    // Set camera forward speed
	virtual void SetCameraFwdSpeed (float _fSpeed) {m_fCameraFwdSpeed = _fSpeed;}

    // Set camera forward speed
	virtual float GetCameraFwdSpeed () const {return m_fCameraFwdSpeed;}

    // Set camera strafe speed
	virtual void SetCameraStrafeSpeed (float _fSpeed) {m_fCameraStrafeSpeed = _fSpeed;}

    // Set camera strafe speed
	virtual float GetCameraStrafeSpeed () const {return m_fCameraStrafeSpeed;}

private:

	std::list<IOGPhysicalObject*>	m_ObjList;
    Vec3    m_vLeftBorder[3];
    Vec3    m_vRightBorder[3];

	float	m_fCameraFwdSpeed;
	float	m_fCameraStrafeSpeed;
};

#endif
