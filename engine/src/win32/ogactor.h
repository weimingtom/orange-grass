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
	COGActor();

public:
	COGActor(OGActorType _Type);
	virtual ~COGActor();

	// Create actor.
	virtual bool Create (
		const std::string& _ModelAlias,
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

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const Vec3& _vRayStart,
        const Vec3& _vRayDir ) const;

protected:

	OGActorType	        m_Type;
    bool                m_bAdded;
	IOGSgNode*	        m_pNode;
    IOGPhysicalObject*  m_pPhysicalObject;
	IOGModel*	        m_pModel;
};


#endif
