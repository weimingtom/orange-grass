/*
 *  IOGActorParams.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGACTORPARAMS_H_
#define IOGACTORPARAMS_H_

#include "IOGPhysicalParams.h"
#include <string>


enum OGActorType
{
	OG_ACTOR_NONE = -1,
	OG_ACTOR_STATIC,
	OG_ACTOR_LANDBOT,
	OG_ACTOR_AIRBOT,
	OG_ACTOR_PLAYER,
	OG_ACTOR_PLASMAMISSILE,
	OG_ACTOR_MISSILE
};


struct IOGActorParams
{
	IOGPhysicalParams	physics;
	OGActorType			type;
	std::string			alias;
	std::string			model_alias;
	std::string			model_propeller_alias;
	std::string			icon;
};


// Parse the actor type string and convert it to internal type
inline OGActorType ParseActorType (const std::string& _ActorTypeStr)
{
	if (_ActorTypeStr.compare(std::string("static")) == 0)
    {
        return OG_ACTOR_STATIC;
    }
    else if (_ActorTypeStr.compare(std::string("land_bot")) == 0)
    {
        return OG_ACTOR_LANDBOT;
    }
    else if (_ActorTypeStr.compare(std::string("air_bot")) == 0)
    {
        return OG_ACTOR_AIRBOT;
    }
    else if (_ActorTypeStr.compare(std::string("player")) == 0)
    {
        return OG_ACTOR_PLAYER;
    }
    else if (_ActorTypeStr.compare(std::string("plasma_missile")) == 0)
    {
        return OG_ACTOR_PLASMAMISSILE;
    }
    else if (_ActorTypeStr.compare(std::string("missile")) == 0)
    {
        return OG_ACTOR_MISSILE;
    }
    return OG_ACTOR_NONE;
}


#endif