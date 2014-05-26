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
#ifndef IOGWEAPON_H_
#define IOGWEAPON_H_

#include "IOGActorParams.h"


class IOGActor;

class IOGWeapon
{
public:
	virtual ~IOGWeapon() {}

	// Create weapon.
	virtual bool Create (IOGActor* _pOwner, IOGWeaponParams* _pWeaponParams) = 0;

	// Fire.
	virtual void Fire (IOGActor* _pTarget, bool _bFollow) = 0;

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime) = 0;

    // Is ready.
    virtual bool IsReady () const = 0;

	// Get params.
	virtual IOGWeaponParams* GetParams () = 0;
};


#endif
