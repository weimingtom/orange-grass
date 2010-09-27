/*
 *  OGWeapon.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGWEAPON_H_
#define OGWEAPON_H_

#include "OGActorPlasmaMissile.h"
#include <list>


class COGWeapon
{
public:
	COGWeapon();
	virtual ~COGWeapon();

	// Create weapon.
	virtual bool Create (IOGActor* _pOwner);

	// Fire missile.
	virtual void Fire (const Vec3& _vTarget);

protected:

    std::list<COGActorPlasmaMissile*>  m_MissileList;
    IOGActor*  m_pOwner;
};


#endif
