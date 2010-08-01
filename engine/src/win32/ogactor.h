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


class COGActor : public IOGActor
{
	COGActor();

public:
	COGActor(OGActorType _Type);
	virtual ~COGActor();

	// Create actor.
	virtual bool Create (
		const char* _pModelAlias,
		const Vec3& _vPos,
		const Vec3& _vRot,
        const Vec3& _vScale);

	// Update actor.
	virtual void Update (int _ElapsedTime);

	// Get actor type.
	virtual OGActorType GetType () const;

	// Get scene graph node.
	virtual IOGSgNode* GetSgNode ();

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const Vec3& _vRayStart,
        const Vec3& _vRayDir ) const;

private:

	IOGSgNode*	m_pNode;
	OGActorType	m_Type;
};


#endif
