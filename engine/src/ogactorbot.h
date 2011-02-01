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

	// Receive damage
	virtual void ReceiveDamage (unsigned int _Damage);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

	// Set actor status.
	virtual void SetFallingStatus ();

	// Set actor status.
	virtual void SetDeadStatus ();

	// Respond on collision with missile.
	virtual bool RespondOnMissileCollision (IOGActor* _pMissile);

	// Respond on collision with missile.
	virtual bool RespondOnBonusCollision (IOGActor* _pBonus);

protected:

    IOGModel*   m_pModelDestruction;
	IOGSgNode*	m_pNodeDestruction;

	IOGEffect*  m_pExplosionEffect;
    IOGSgNode*  m_pExplosionNode;

	COGWeapon*	m_pWeapon;

	struct PartsTrail
	{
	    IOGEffect*  m_pTrailEffect;
		IOGSgNode*  m_pTrailNode;
	};
	typedef std::vector<PartsTrail>	TTrailList;
	TTrailList	m_TrailList;
};


#endif
