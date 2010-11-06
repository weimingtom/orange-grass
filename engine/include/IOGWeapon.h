/*
 *  IOGWeapon.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
