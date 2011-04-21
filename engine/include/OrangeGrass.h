/*
 *  OrangeGrass.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef ORANGEGRASS_H_
#define ORANGEGRASS_H_

#include "IOGCoreHelpers.h"
#include "IOGResourceMgr.h"
#include "IOGLevelManager.h"
#include "IOGSceneGraph.h"
#include "IOGActorManager.h"
#include "IOGSpritePool.h"
#include "IOGPhysics.h"
#include "IOGInputDispatcher.h"
#include "IOGRenderer.h"
#include "IOGStatistics.h"
#include "IOGEffectsManager.h"
#include "IOGActorParamsManager.h"
#include "IOGGlobalVarsTable.h"
#include "IOGSettingsReader.h"
#include "IOGAppSettings.h"
#include "IOGGameSequence.h"
#include "IOGLuaVM.h"
#include "common.h"

void StartOrangeGrass();
void FinishOrangeGrass();

IOGResourceMgr* GetResourceMgr ();
IOGLevelManager* GetLevelManager ();
IOGSceneGraph* GetSceneGraph ();
IOGActorManager* GetActorManager ();
IOGPhysics* GetPhysics ();
IOGInputDispatcher* GetInput ();
IOGRenderer* GetRenderer ();
IOGStatistics* GetStatistics ();
IOGSpritePool* GetSpritePool ();
IOGEffectsManager* GetEffectsManager ();
IOGActorParamsMgr* GetActorParamsMgr ();
IOGGlobalVarsTable* GetGlobalVars ();
IOGSettingsReader* GetSettingsReader ();
IOGAppSettings* GetAppSettings ();
IOGGameSequence* GetGameSequence ();
IOGLuaVM* GetLuaVM ();


// Parse the actor type string and convert it to internal type
OGActorType ParseActorType (const std::string& _ActorTypeStr);

// Parse the physics type string and convert it to internal type
OGPhysicsType ParsePhysicsType (const std::string& _PhysicsTypeStr);

// Parse the weapon position type string and convert it to internal type
OGWeaponPos ParseWeaponPositionType (const std::string& _WeaponPosTypeStr);

// Parse the bonus type string and convert it to internal type
OGBonusType ParseBonusType (const std::string& _BonusTypeStr);

// Parse the blend type string and convert it to internal type
OGBlendType ParseBlendType (const std::string& _BlendTypeStr);

#endif