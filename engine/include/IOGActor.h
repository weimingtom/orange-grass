/*
 *  IOGActor.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGACTOR_H_
#define IOGACTOR_H_

#include "IOGSgNode.h"


enum OGActorType
{
	OG_ACTOR_NONE = -1,
	OG_ACTOR_STATIC,
	OG_ACTOR_LANDBOT
};


class IOGActor
{
public:
	virtual ~IOGActor() {}

	// Update actor.
	virtual void Update (int _ElapsedTime) = 0;

	// Get actor type.
	virtual OGActorType GetType () const = 0;

	// Get scene graph node.
	virtual IOGSgNode* GetSgNode () = 0;

	// Check actor's OBB intersection with ray.
	virtual bool CheckIntersection (
        const Vec3& _vRayStart,
        const Vec3& _vRayDir ) const = 0;
};


#endif
