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
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale);

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

	//struct PartsTrail
	//{
	//    IOGEffect*  m_pTrailEffect;
	//	IOGSgNode*  m_pTrailNode;
	//};
	//typedef std::vector<PartsTrail>	TTrailList;
	//TTrailList	m_TrailList;
};


#endif
