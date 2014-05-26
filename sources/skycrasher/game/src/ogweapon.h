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
#ifndef OGWEAPON_H_
#define OGWEAPON_H_

#include "ogactorbullet.h"
#include "IOGWeapon.h"
#include <vector>


class COGWeapon : public IOGWeapon
{
public:
	COGWeapon();
	virtual ~COGWeapon();

	// Create weapon.
	virtual bool Create (IOGActor* _pOwner, IOGWeaponParams* _pWeaponParams);

	// Fire.
	virtual void Fire (IOGActor* _pTarget, bool _bFollow);

	// Fire.
	virtual void Fire (const OGVec3& _vTarget);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

    // Is ready.
    virtual bool IsReady () const;

	// Get params.
	virtual IOGWeaponParams* GetParams () {return m_pWeaponParams;}

protected:

	typedef std::vector<COGActorBullet*>	TMissileList;

	TMissileList		m_MissileList;
    IOGActor*			m_pOwner;
	IOGWeaponParams*	m_pWeaponParams;
    unsigned long		m_WeaponCoolDown;
    unsigned long		m_WeaponCoolDownMax;
};


#endif
