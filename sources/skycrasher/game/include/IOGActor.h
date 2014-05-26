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
#ifndef IOGACTOR_H_
#define IOGACTOR_H_

#include "IOGSgNode.h"
#include "IOGActorParams.h"
#include "IOGPhysicalObject.h"
#include "IOGWeapon.h"
#include "IOGGameEventsHandler.h"


enum OGActorStatus
{
	OG_ACTORSTATUS_ALIVE,
	OG_ACTORSTATUS_FALLING,
	OG_ACTORSTATUS_DEAD
};


class IOGActor
{
public:
	virtual ~IOGActor() {}

	// Set game event handler.
	virtual void SetGameEventHandler (IOGGameEventsHandler* _pHandler) = 0;

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime) = 0;

	// Update actors in editor.
	virtual void UpdateEditor (unsigned long _ElapsedTime) = 0;

	// Adding to actor manager event handler.
	virtual void OnAddedToManager () = 0;

	// Get actor type.
	virtual OGActorType GetType () const = 0;

	// Set actor team.
	virtual void SetTeam (OGTeam _Team) = 0;

	// Get actor team.
	virtual OGTeam GetTeam () const = 0;

	// Get damage points.
	virtual unsigned int GetDamagePoints () const = 0;

	// Get hitpoints.
    virtual unsigned int GetHitPoints () const = 0;

	// Get scene graph node.
	virtual IOGSgNode* GetSgNode () = 0;

	// Get physical object.
	virtual IOGPhysicalObject* GetPhysicalObject () = 0;

	// Get actor params.
	virtual IOGActorParams* GetParams () = 0;

	// Get model alias
	virtual const std::string& GetAlias () const = 0;

	// Set weapon parameters.
	virtual void SetWeapon (IOGWeaponParams* _pWeaponParams) = 0;

	// Get weapon
	virtual IOGWeapon* GetWeapon () = 0;

	// Set bonus parameters.
	virtual void SetBonusParams (IOGBonusParams* _pBonusParams) = 0;

	// Get bonus params
	virtual IOGBonusParams* GetBonusParams () = 0;

	// Get special params
    virtual void GetSpecialParams (std::vector<IOGBonusParams>& _ParamsList) = 0;

	// Get active state
	virtual bool IsActive () const = 0;

	// Set active state
	virtual void Activate (bool _bActive) = 0;

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const OGVec3& _vRayStart,
        const OGVec3& _vRayDir ) const = 0;
};


#endif
