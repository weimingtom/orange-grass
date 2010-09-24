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
	OG_PHYSICS_PLAYER,
	OG_PHYSICS_MISSILE
};


struct IOGPhysicalParams
{
    IOGPhysicalParams()
    {
		type = OG_PHYSICS_STATIC;
        fMaxSpeed = 0.0f;
    }

    OGPhysicsType type;
	float fMaxSpeed;
};


// Parse the physics type string and convert it to internal type
inline OGPhysicsType ParsePhysicsType (const std::string& _PhysicsTypeStr)
{
	if (_PhysicsTypeStr.compare(std::string("static")) == 0)
    {
        return OG_PHYSICS_STATIC;
    }
    else if (_PhysicsTypeStr.compare(std::string("land_bot")) == 0)
    {
        return OG_PHYSICS_LANDBOT;
    }
    else if (_PhysicsTypeStr.compare(std::string("air_bot")) == 0)
    {
        return OG_PHYSICS_AIRBOT;
    }
    else if (_PhysicsTypeStr.compare(std::string("player")) == 0)
    {
        return OG_PHYSICS_PLAYER;
    }
    else if (_PhysicsTypeStr.compare(std::string("missile")) == 0)
    {
        return OG_PHYSICS_MISSILE;
    }
    return OG_PHYSICS_NONE;
}


#endif