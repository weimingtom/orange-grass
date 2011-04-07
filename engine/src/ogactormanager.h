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
#include <vector>


class COGActorManager : public IOGActorManager
{
public:
	COGActorManager ();
	virtual ~COGActorManager ();

	// Clear actors manager
	virtual void Clear ();

	// Create actor
	virtual IOGActor* CreateActor (
		const std::string& _Alias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Add actor to the list.
	virtual void AddActor (IOGActor* _pActor);

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor);

	// Update actors.
	virtual void Update (unsigned long _ElapsedTime);

	// Update actors in editor.
	virtual void UpdateEditor (unsigned long _ElapsedTime);

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const Vec3& _RayStart, 
        const Vec3& _RayDir );

	// Get actors list.
    virtual const TActorsList& GetActorsList () const;

	// Get player's actor.
    virtual IOGActor* GetPlayersActor ();

private:
	typedef std::vector<IOGActor*> TActorsList;

	IOGGlobalVarsTable* m_pGlobalVars;
    TActorsList			m_ActorsList;
    TActorsList			m_MissileActorsList;
	IOGActor*			m_pPlayersActor;
};

#endif
