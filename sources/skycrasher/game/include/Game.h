/*
 *  Game.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef GAME_H_
#define GAME_H_

#include "OrangeGrass.h"
#include "IOGLevelManager.h"
#include "IOGSceneGraph.h"
#include "IOGActorManager.h"
#include "IOGSpritePool.h"
#include "IOGPhysics.h"
#include "IOGActorParamsManager.h"
#include "IOGAppSettings.h"
#include "IOGGameSequence.h"
#include "IOGGameSystem.h"


IOGLevelManager* GetLevelManager ();
IOGSceneGraph* GetSceneGraph ();
IOGActorManager* GetActorManager ();
IOGPhysics* GetPhysics ();
IOGSpritePool* GetSpritePool ();
IOGActorParamsMgr* GetActorParamsMgr ();
IOGAppSettings* GetAppSettings ();
IOGGameSequence* GetGameSequence ();
IOGGameSystem* GetGame ();


void StartGameCore();
void FinishGameCore();

// Parse the actor type string and convert it to internal type
OGActorType ParseActorType (const std::string& _ActorTypeStr);

// Parse the physics type string and convert it to internal type
OGPhysicsType ParsePhysicsType (const std::string& _PhysicsTypeStr);

// Parse the weapon position type string and convert it to internal type
OGWeaponPos ParseWeaponPositionType (const std::string& _WeaponPosTypeStr);

// Parse the bonus type string and convert it to internal type
OGBonusType ParseBonusType (const std::string& _BonusTypeStr);


#endif