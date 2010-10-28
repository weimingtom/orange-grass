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

#include "Mathematics.h"
#include "IOGObb.h"


enum OGPhysicsType
{
	OG_PHYSICS_NONE = -1,
	OG_PHYSICS_STATIC,
	OG_PHYSICS_LANDBOT,
	OG_PHYSICS_AIRBOT,
	OG_PHYSICS_PLAYER,
	OG_PHYSICS_MISSILE,
	OG_PHYSICS_BONUS
};


struct IOGPhysicalParams
{
    IOGPhysicalParams()
    {
		type = OG_PHYSICS_STATIC;
        fMaxSpeed = 0.0f;
        fAcceleration = 0.0f;
        fStrafeMaxSpeed = 0.0f;
	    fRollSpeed = 0.0f;
	    fMaxRollAngle = 0.0f;
	    fTorque = 0.0f;
    }

    OGPhysicsType type;
	float fMaxSpeed;
	float fAcceleration;
	float fStrafeMaxSpeed;
	float fRollSpeed;
	float fMaxRollAngle;
	float fTorque;
};

#endif