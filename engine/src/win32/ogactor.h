/*
 *  OGActor.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale) = 0;

	// Update actor.
	virtual void Update (unsigned long _ElapsedTime);

	// Update actors in editor.
	virtual void UpdateEditor (unsigned long _ElapsedTime);

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Get actor type.
	virtual OGActorType GetType () const;

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

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const Vec3& _vRayStart,
        const Vec3& _vRayDir ) const;

    // collision event handler
	virtual bool OnCollision (const IOGCollision& _Collision);

protected:

    bool				m_bActive;
	bool                m_bAdded;
	IOGActorParams*		m_pParams;
	IOGSgNode*	        m_pNode;
    IOGPhysicalObject*  m_pPhysicalObject;
	IOGModel*	        m_pModel;
	OGActorStatus		m_Status;
};


#endif
