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

	// Fire to target.
	virtual void Fire (const Vec3& _vTarget);

protected:

	IOGActor*   m_pOwner;
    Vec3        m_vLaunchOffset;
};


#endif
