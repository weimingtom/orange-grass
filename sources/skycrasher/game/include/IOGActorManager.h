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
#ifndef IOGACTORMANAGER_H_
#define IOGACTORMANAGER_H_

#include "IOGActor.h"
#include <vector>
#include <string>


class IOGActorManager
{
public:
	typedef std::vector<IOGActor*>    TActorsList;

public:
	// destructor
	virtual ~IOGActorManager () {}

	// Clear actors manager
	virtual void Clear () = 0;

	// Create actor
	virtual IOGActor* CreateActor (
		const std::string& _Alias,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale) = 0;

	// Add actor to the list.
	virtual void AddActor (IOGActor* _pActor) = 0;

	// Destroy actor and remove from list.
	virtual void DestroyActor (IOGActor* _pActor) = 0;

	// Update actors.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update actors in editor.
	virtual void UpdateEditor (unsigned long _ElapsedTime) = 0;

	// Get player's actor.
    virtual IOGActor* GetPlayersActor () = 0;

	// Get actors list.
    virtual const TActorsList& GetActorsList () const = 0;

	// Get nearest intersected actor.
	virtual IOGActor* GetNearestIntersectedActor (
        const OGVec3& _RayStart, 
        const OGVec3& _RayDir ) = 0;
};

#endif
