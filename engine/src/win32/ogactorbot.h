/*
 *  OGActorAirbot.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORBOT_H_
#define OGACTORBOT_H_

#include "ogactor.h"
#include "IOGCollisionListener.h"
#include "ogweapon.h"


class COGActorBot : public COGActor
{
public:
	COGActorBot();
	virtual ~COGActorBot();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

	// Set weapon
	virtual void SetWeapon (IOGWeaponParams* _pWeaponParams);

	// Get weapon
	virtual IOGWeapon* GetWeapon () {return m_pWeapon;}

	// Set active state
	virtual void Activate (bool _bActive);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

protected:

	IOGSgNode*	m_pNodePropeller;
    IOGModel*   m_pModelPropeller;

	IOGSgNode*	m_pNodeDestruction;
    IOGModel*   m_pModelDestruction;

	IOGEffect*  m_pExplosionEffect;
    IOGSgNode*  m_pExplosionNode;
    IOGEffect*  m_pTrailEffect;
    IOGSgNode*  m_pTrailNode;

	COGWeapon*	m_pWeapon;
};


#endif
