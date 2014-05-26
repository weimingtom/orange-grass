/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
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