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
#include "IOGMaterialManager.h"
#include "IOGStatistics.h"
#include "IOGEffectsManager.h"
#include "IOGActorParamsManager.h"
#include "IOGGlobalVarsTable.h"
#include "IOGSettingsReader.h"
#include "IOGAppSettings.h"
#include "common.h"


IOGResourceMgr* GetResourceMgr ();
IOGLevelManager* GetLevelManager ();
IOGSceneGraph* GetSceneGraph ();
IOGActorManager* GetActorManager ();
IOGPhysics* GetPhysics ();
IOGInputDispatcher* GetInput ();
IOGRenderer* GetRenderer ();
IOGRenderer* GetRendererGL11 ();
IOGMaterialManager* GetMaterialManager ();
IOGStatistics* GetStatistics ();
IOGSpritePool* GetSpritePool ();
IOGEffectsManager* GetEffectsManager ();
IOGActorParamsMgr* GetActorParamsMgr ();
IOGGlobalVarsTable* GetGlobalVars ();
IOGSettingsReader* GetSettingsReader ();
IOGAppSettings* GetAppSettings ();

#endif