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
	OG_ACTOR_MISSILE,
	OG_ACTOR_BONUS,
    OG_ACTOR_GAUSSRAY
};


enum OGTeam
{
	TEAM_NEUTRAL = 0,
	TEAM_PLAYER,
	TEAM_ENEMY
};


enum OGWeaponPos
{
    OG_WEAPONPOS_NONE = -1,
	OG_WEAPONPOS_CENTER,
	OG_WEAPONPOS_LEFT,
	OG_WEAPONPOS_RIGHT,
	OG_WEAPONPOS_LEFTRIGHT,
	OG_WEAPONPOS_CENTERLEFTRIGHT
};


struct IOGWeaponParams
{
	std::string		alias;
	unsigned int	hitpoints;
	unsigned int	cooldown;
	OGWeaponPos		pos;
	std::string		actor;
	std::string		icon_texture;
};


enum OGBonusType
{
    OG_BONUS_NONE = -1,
	OG_BONUS_LIFEPACK,
	OG_BONUS_SHIELD,
};


struct IOGBonusParams
{
	std::string		alias;
	unsigned int	value;
	unsigned int	cooldown;
	OGBonusType		type;
	std::string		actor;
	std::string		icon_texture;
};


struct IOGGameplayParams
{
	IOGGameplayParams()
	{
		max_hitpoints = 0;
		hitpoints = max_hitpoints;
		team = TEAM_NEUTRAL;
	}

	unsigned int	max_hitpoints;
	unsigned int	hitpoints;
    std::string     weapon;
	OGTeam			team;
};


struct IOGActorParams
{
	IOGPhysicalParams	physics;
	IOGGameplayParams	gameplay;
	OGActorType			type;
	std::string			alias;
	std::string			model_alias;
	std::string			model_propeller_alias;
	std::string			model_destruction;
	std::string			icon;
};

#endif