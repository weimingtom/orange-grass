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
	virtual void Fire ();

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
