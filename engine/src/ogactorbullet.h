/*
 *  OGActorBullet.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORBULLET_H_
#define OGACTORBULLET_H_

#include "ogactor.h"


class COGActorBullet : public COGActor
{
public:
	COGActorBullet();
	virtual ~COGActorBullet();

	// Set owner.
	virtual void SetOwner (IOGActor* _pOwner, const Vec3& _vLaunchOffset);

	// Set target.
	virtual void SetTarget (IOGActor* _pTarget);

	// Set target.
	virtual void SetTarget (const Vec3& _vTarget);

	// Set damage points.
	virtual void SetDamagePoints (unsigned int _DamagePoints);

	// Fire.
	virtual void Fire ();

protected:

	IOGActor*   m_pOwner;
	IOGActor*   m_pTarget;
	Vec3		m_vTarget;
    Vec3        m_vLaunchOffset;
};


#endif
