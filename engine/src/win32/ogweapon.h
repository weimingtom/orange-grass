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
#include <list>


class COGWeapon
{
public:
	COGWeapon();
	virtual ~COGWeapon();

	// Create weapon.
	virtual bool Create (IOGActor* _pOwner, const std::string& _Alias, const Vec3& _vLaunchPos);

	// Fire missile.
	virtual void Fire (const Vec3& _vTarget);

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

    // Is ready.
    virtual bool IsReady () const;

protected:

    std::list<COGActorBullet*>  m_MissileList;
    IOGActor*                   m_pOwner;
    Vec3                        m_vLaunchPos;
    unsigned long               m_WeaponCoolDown;
    unsigned long               m_WeaponCoolDownMax;
};


#endif
