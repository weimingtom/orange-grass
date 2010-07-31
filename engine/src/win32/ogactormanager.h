/*
 *  GActorManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORMANAGER_H_
#define OGACTORMANAGER_H_

#include "IOGActorManager.h"


class COGActorManager : public IOGActorManager
{
public:
	COGActorManager ();
	virtual ~COGActorManager ();

	// Create static actor
	virtual IOGActor* CreateStaticActor (
		const char* _pModelAlias,
		const MATRIX& _mWorld);

	// Create bot actor
	virtual IOGActor* CreateBotActor (
		const char* _pModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot);

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor);

	// Update actors.
	virtual void Update (int _ElapsedTime);

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const Vec3& _LineStart, 
        const Vec3& _LineEnd );

private:

    std::vector<IOGActor*>	m_ActorsList;
};

#endif
