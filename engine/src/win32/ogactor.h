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


class COGActor : public IOGActor
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

	// Adding to actor manager event handler.
	virtual void OnAddedToManager ();

	// Get actor type.
	virtual OGActorType GetType () const;

	// Get scene graph node.
	virtual IOGSgNode* GetSgNode ();

	// Get physical object.
	virtual IOGPhysicalObject* GetPhysicalObject ();

	// Get model alias
	virtual const std::string& GetAlias () const;

	// Get active state
	virtual bool IsActive () const { return m_bActive; }

	// Set active state
	virtual void Activate (bool _bActive);

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const Vec3& _vRayStart,
        const Vec3& _vRayDir ) const;

protected:

    bool				m_bActive;
	bool                m_bAdded;
	IOGActorParams*		m_pParams;
	IOGSgNode*	        m_pNode;
	IOGSgNode*	        m_pNodePropeller;
    IOGPhysicalObject*  m_pPhysicalObject;
	IOGModel*	        m_pModel;
    IOGModel*           m_pModelPropeller;
};


#endif
