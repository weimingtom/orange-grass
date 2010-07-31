/*
 *  IOGActorManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGACTORMANAGER_H_
#define IOGACTORMANAGER_H_

#include "IOGActor.h"


class IOGActorManager
{
public:
	// destructor
	virtual ~IOGActorManager () {}

	// Create static actor
	virtual IOGActor* CreateStaticActor (
		const char* _pModelAlias,
		const MATRIX& _mWorld) = 0;

	// Create bot actor
	virtual IOGActor* CreateBotActor (
		const char* _pModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot) = 0;

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor) = 0;

	// Update actors.
	virtual void Update (int _ElapsedTime) = 0;

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const Vec3& _LineStart, 
        const Vec3& _LineEnd ) = 0;
};

#endif
