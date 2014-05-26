/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
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
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

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
        const OGVec3& _RayStart, 
        const OGVec3& _RayDir );

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
