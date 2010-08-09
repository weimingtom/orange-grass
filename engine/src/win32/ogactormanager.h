/*
 *  OGActorManager.h
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

	// Clear actors manager
	virtual void Clear ();

	// Create actor
	virtual IOGActor* CreateActor (
		OGActorType _Type,
		const std::string& _ModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Add actor to the list.
	virtual void AddActor (IOGActor* _pActor);

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor);

	// Update actors.
	virtual void Update (int _ElapsedTime);

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const Vec3& _RayStart, 
        const Vec3& _RayDir );

	// Get actors list.
    virtual const std::vector<IOGActor*>& GetActorsList () const;

	// Parse the actor type string and convert it to internal type
	virtual OGActorType ParseActorType (const std::string& _ActorTypeStr);

private:

    std::vector<IOGActor*>	m_ActorsList;
};

#endif
