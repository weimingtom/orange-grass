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
#include <list>


class COGWeapon : public IOGWeapon
{
public:
	COGWeapon();
	virtual ~COGWeapon();

	// Create weapon.
	virtual bool Create (IOGActor* _pOwner, IOGWeaponParams* _pWeaponParams, const Vec3& _vLaunchPos);

	// Fire missile.
	virtual void Fire (const Vec3& _vTarget);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

    // Is ready.
    virtual bool IsReady () const;

	// Get params.
	virtual IOGWeaponParams* GetParams () {return m_pWeaponParams;}

protected:

    std::list<COGActorBullet*>  m_MissileList;
    IOGActor*                   m_pOwner;
	IOGWeaponParams*			m_pWeaponParams;
    Vec3                        m_vLaunchPos;
    unsigned long               m_WeaponCoolDown;
    unsigned long               m_WeaponCoolDownMax;
};


#endif
