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
#ifndef OGACTOR_H_
#define OGACTOR_H_

#include "IOGActor.h"
#include <string>


class COGActor : public IOGActor, public IOGCollisionListener
{
public:
	COGActor();
	virtual ~COGActor();

	// Create actor.
	virtual bool Create (
		IOGActorParams* _pParams,
		const OGVec3& _vPos,
		const OGVec3& _vRot,
        const OGVec3& _vScale) = 0;

	// Set game event handler.
    virtual void SetGameEventHandler (IOGGameEventsHandler* _pHandler) {m_pGameEventsHandler = _pHandler;}

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Update actors in editor.
	virtual void UpdateEditor (unsigned long _ElapsedTime);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Get actor type.
	virtual OGActorType GetType () const;

	// Set actor team.
	virtual void SetTeam (OGTeam _Team);

	// Get actor team.
	virtual OGTeam GetTeam () const;

	// Get damage points.
	virtual unsigned int GetDamagePoints () const;

	// Get hitpoints.
    virtual unsigned int GetHitPoints () const {return m_Hitpoints;}

	// Get scene graph node.
	virtual IOGSgNode* GetSgNode ();

	// Get physical object.
	virtual IOGPhysicalObject* GetPhysicalObject ();

	// Get actor params.
	virtual IOGActorParams* GetParams () {return m_pParams;}

	// Get model alias
	virtual const std::string& GetAlias () const;

	// Set weapon
	virtual void SetWeapon (IOGWeaponParams* _pWeaponParams) {}

	// Get weapon
	virtual IOGWeapon* GetWeapon () {return NULL;}

	// Set bonus parameters.
    virtual void SetBonusParams (IOGBonusParams* _pBonusParams) {}

	// Get bonus params
    virtual IOGBonusParams* GetBonusParams () {return NULL;}

	// Get special params
    virtual void GetSpecialParams (std::vector<IOGBonusParams>& _ParamsList) {}

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const OGVec3& _vRayStart,
        const OGVec3& _vRayDir ) const;

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

	// Update alive actor.
	virtual void UpdateAlive (unsigned long _ElapsedTime);

	// Update falling actor.
	virtual void UpdateFalling (unsigned long _ElapsedTime);

protected:

    bool				m_bActive;
	bool                m_bAdded;
	IOGActorParams*		m_pParams;
	IOGSgNode*	        m_pNode;
    IOGPhysicalObject*  m_pPhysicalObject;
	IOGModel*	        m_pModel;
	OGActorStatus		m_Status;
    OGTeam              m_Team;
    unsigned int        m_DamagePoints;
    unsigned int        m_Hitpoints;
    IOGGameEventsHandler* m_pGameEventsHandler;

	IOGSceneGraph*		m_pSg;
	IOGPhysics*			m_pPhysics;
};


#endif
