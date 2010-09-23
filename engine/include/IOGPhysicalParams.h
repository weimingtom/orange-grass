/*
 *  IOGPhysicalParams.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGPHYSICALPARAMS_H_
#define IOGPHYSICALPARAMS_H_

#include "IOGMath.h"
#include "IOGObb.h"


enum OGPhysicsType
{
	OG_PHYSICS_NONE = -1,
	OG_PHYSICS_STATIC,
	OG_PHYSICS_LANDBOT,
	OG_PHYSICS_AIRBOT,
	OG_PHYSICS_PLAYER
};


struct IOGPhysicalParams
{
    IOGPhysicalParams()
    {
        fMaxSpeed = 0.0f;
    }

    float fMaxSpeed;
};


#endif