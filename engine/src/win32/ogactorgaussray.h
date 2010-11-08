/*
 *  OGActorGaussRay.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORGAUSSRAY_H_
#define OGACTORGAUSSRAY_H_

#include "ogactorbullet.h"


class COGActorGaussRay : public COGActorBullet
{
public:
	COGActorGaussRay();
	virtual ~COGActorGaussRay();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Set active state
	virtual void Activate (bool _bActive);

	// Fire.
	virtual void Fire ();

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

protected:

    IOGEffect*				m_pHeadEffect;
    IOGEffect*				m_pCollisionEffect;
    IOGSgNode*              m_pCollisionEffectNode;
};


#endif
