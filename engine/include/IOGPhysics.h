/*
 *  IOGPhysics.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGPHYSICS_H_
#define IOGPHYSICS_H_

#include "IOGPhysicalObject.h"


class IOGPhysics
{
public:
	// destructor
	virtual ~IOGPhysics () {}

	// Clear scene graph
	virtual void Clear () = 0;

	// Create object
	virtual IOGPhysicalObject* CreateObject (
		IOGPhysicalParams* _pParams,
		const IOGAabb& _Aabb,
        void* _pActor) = 0;

	// Add object
	virtual void AddObject (IOGPhysicalObject* _pObject) = 0;

	// Remove object
	virtual void RemoveObject (IOGPhysicalObject* _pObject) = 0;

    // Set level borders
    virtual void SetLevelBorders (const Vec3& _vStart, const Vec3& _vFinish, float _fWidth) = 0;

    // Get borders at point
    virtual void GetBordersAtPoint (const Vec3& _vPos, Vec3& _vLeft, Vec3& _vRight) = 0;

	// Update transforms.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update transforms for the whole scene.
	virtual void UpdateAll (unsigned long _ElapsedTime) = 0;
};

#endif
