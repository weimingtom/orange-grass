/*
 *  OrangeGrass.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "oglevelmanager.h"
#include "ogscenegraph.h"
#include "ogactormanager.h"
#include "ogphysics.h"
#include "oginputdispatcher.h"
#include "ogrenderer.h"
#include "ogspritepool.h"
#include "ogstatistics.h"
#include "ogeffectsmanager.h"
#include "ogactorparamsmgr.h"
#include "ogglobalvarstable.h"
#include "ogsettingsreader.h"
#include "ogappsettings.h"
#include "oggamesequence.h"
#include "ogfpscounter.h"
#include <map>


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGLevelManager* g_pLevelMgr = NULL;
static IOGSceneGraph* g_pSg = NULL;
static IOGActorManager* g_pActorMgr = NULL;
static IOGPhysics* g_pPhysics = NULL;
static IOGInputDispatcher* g_pInput = NULL;
static IOGRenderer* g_pRenderer = NULL;
static IOGStatistics* g_pStats = NULL;
static IOGSpritePool* g_pSprPool = NULL;
static IOGEffectsManager* g_pEffectsMgr = NULL;
static IOGActorParamsMgr* g_pActorParamsMgr = NULL;
static IOGGlobalVarsTable* g_pGlobalVars = NULL;
static IOGSettingsReader* g_pSettingsReader = NULL;
static IOGAppSettings* g_pAppSettings = NULL;
static IOGGameSequence* g_pGameSequence = NULL;
static IOGFPSCounter* g_pFPS = NULL;

static std::map<std::string, OGActorType> g_ActorTypeLookup;
static std::map<std::string, OGPhysicsType> g_PhysicsTypeLookup;
static std::map<std::string, OGWeaponPos> g_WeaponPosLookup;
static std::map<std::string, OGBonusType> g_BonusTypeLookup;
static std::map<std::string, OGBlendType> g_BlendTypeLookup;


void StartOrangeGrass()
{
	g_ActorTypeLookup["static"] = OG_ACTOR_STATIC;
	g_ActorTypeLookup["land_bot"] = OG_ACTOR_LANDBOT;
	g_ActorTypeLookup["air_bot"] = OG_ACTOR_AIRBOT;
	g_ActorTypeLookup["player"] = OG_ACTOR_PLAYER;
	g_ActorTypeLookup["plasma_missile"] = OG_ACTOR_PLASMAMISSILE;
	g_ActorTypeLookup["missile"] = OG_ACTOR_MISSILE;
	g_ActorTypeLookup["bonus"] = OG_ACTOR_BONUS;
	g_ActorTypeLookup["gaussray"] = OG_ACTOR_GAUSSRAY;

	g_PhysicsTypeLookup["static"] = OG_PHYSICS_STATIC;
	g_PhysicsTypeLookup["land_bot"] = OG_PHYSICS_LANDBOT;
	g_PhysicsTypeLookup["air_bot"] = OG_PHYSICS_AIRBOT;
	g_PhysicsTypeLookup["player"] = OG_PHYSICS_PLAYER;
	g_PhysicsTypeLookup["missile"] = OG_PHYSICS_MISSILE;
	g_PhysicsTypeLookup["bonus"] = OG_PHYSICS_BONUS;

	g_WeaponPosLookup["center"] = OG_WEAPONPOS_CENTER;
	g_WeaponPosLookup["left"] = OG_WEAPONPOS_LEFT;
	g_WeaponPosLookup["right"] = OG_WEAPONPOS_RIGHT;
	g_WeaponPosLookup["left_right"] = OG_WEAPONPOS_LEFTRIGHT;
	g_WeaponPosLookup["center_left_right"] = OG_WEAPONPOS_CENTERLEFTRIGHT;

	g_BonusTypeLookup["life_pack"] = OG_BONUS_LIFEPACK;
	g_BonusTypeLookup["shield"] = OG_BONUS_SHIELD;

	g_BlendTypeLookup["solid"] = OG_BLEND_SOLID;
	g_BlendTypeLookup["test"] = OG_BLEND_ALPHATEST;
	g_BlendTypeLookup["blend"] = OG_BLEND_ALPHABLEND;
	g_BlendTypeLookup["add"] = OG_BLEND_ALPHAADD;
}


void FinishOrangeGrass()
{
	g_ActorTypeLookup.clear();
	g_PhysicsTypeLookup.clear();
	g_WeaponPosLookup.clear();
	g_BonusTypeLookup.clear();
	g_BlendTypeLookup.clear();
}


// Parse the actor type string and convert it to internal type
OGActorType ParseActorType (const std::string& _ActorTypeStr)
{
    std::map<std::string, OGActorType>::const_iterator iter = g_ActorTypeLookup.find(_ActorTypeStr);
    if (iter != g_ActorTypeLookup.end())
    {
        return iter->second;
    }
    return OG_ACTOR_NONE;
}


// Parse the physics type string and convert it to internal type
OGPhysicsType ParsePhysicsType (const std::string& _PhysicsTypeStr)
{
    std::map<std::string, OGPhysicsType>::const_iterator iter = g_PhysicsTypeLookup.find(_PhysicsTypeStr);
    if (iter != g_PhysicsTypeLookup.end())
    {
        return iter->second;
    }
    return OG_PHYSICS_NONE;
}


// Parse the weapon position type string and convert it to internal type
OGWeaponPos ParseWeaponPositionType (const std::string& _WeaponPosTypeStr)
{
    std::map<std::string, OGWeaponPos>::const_iterator iter = g_WeaponPosLookup.find(_WeaponPosTypeStr);
    if (iter != g_WeaponPosLookup.end())
    {
        return iter->second;
    }
    return OG_WEAPONPOS_NONE;
}


// Parse the bonus type string and convert it to internal type
OGBonusType ParseBonusType (const std::string& _BonusTypeStr)
{
    std::map<std::string, OGBonusType>::const_iterator iter = g_BonusTypeLookup.find(_BonusTypeStr);
    if (iter != g_BonusTypeLookup.end())
    {
        return iter->second;
    }
    return OG_BONUS_NONE;
}


// Parse the blend type string and convert it to internal type
OGBlendType ParseBlendType (const std::string& _BlendTypeStr)
{
    std::map<std::string, OGBlendType>::const_iterator iter = g_BlendTypeLookup.find(_BlendTypeStr);
    if (iter != g_BlendTypeLookup.end())
    {
        return iter->second;
    }
    return OG_BLEND_NO;
}


IOGResourceMgr* GetResourceMgr ()
{
	if (g_pResourceMgr == NULL)
	{
		g_pResourceMgr = new COGResourceMgr ();
	}
	return g_pResourceMgr;
}


IOGLevelManager* GetLevelManager ()
{
	if (g_pLevelMgr == NULL)
	{
		g_pLevelMgr = new COGLevelManager ();
	}
	return g_pLevelMgr;
}


IOGSceneGraph* GetSceneGraph ()
{
	if (g_pSg == NULL)
	{
		g_pSg = new COGSceneGraph ();
	}
	return g_pSg;
}


IOGActorManager* GetActorManager ()
{
	if (g_pActorMgr == NULL)
	{
		g_pActorMgr = new COGActorManager ();
	}
	return g_pActorMgr;
}


IOGPhysics* GetPhysics ()
{
	if (g_pPhysics == NULL)
	{
		g_pPhysics = new COGPhysics ();
	}
	return g_pPhysics;
}


IOGInputDispatcher* GetInput ()
{
	if (g_pInput == NULL)
	{
		g_pInput = new COGInputDispatcher ();
	}
	return g_pInput;
}


IOGRenderer* GetRenderer ()
{
	if (g_pRenderer == NULL)
	{
		g_pRenderer = new COGRenderer ();
		g_pRenderer->Init();
	}
	return g_pRenderer;
}


IOGStatistics* GetStatistics ()
{
	if (g_pStats == NULL)
	{
		g_pStats = new COGStatistics ();
	}
	return g_pStats;
}


IOGSpritePool* GetSpritePool ()
{
	if (g_pSprPool == NULL)
	{
		g_pSprPool = new COGSpritePool ();
	}
	return g_pSprPool;
}


IOGEffectsManager* GetEffectsManager ()
{
	if (g_pEffectsMgr == NULL)
	{
		g_pEffectsMgr = new COGEffectsManager ();
	}
	return g_pEffectsMgr;
}


IOGActorParamsMgr* GetActorParamsMgr ()
{
	if (g_pActorParamsMgr == NULL)
	{
		g_pActorParamsMgr = new COGActorParamsMgr ();
	}
	return g_pActorParamsMgr;
}


IOGGlobalVarsTable* GetGlobalVars ()
{
	if (g_pGlobalVars == NULL)
	{
		g_pGlobalVars = new COGGlobalVarsTable ();
	}
	return g_pGlobalVars;
}


IOGSettingsReader* GetSettingsReader ()
{
	if (g_pSettingsReader == NULL)
	{
		g_pSettingsReader = new COGSettingsReader ();
	}
	return g_pSettingsReader;
}


IOGAppSettings* GetAppSettings ()
{
	if (g_pAppSettings == NULL)
	{
		g_pAppSettings = new COGAppSettings ();
	}
	return g_pAppSettings;
}


IOGGameSequence* GetGameSequence ()
{
	if (g_pGameSequence == NULL)
	{
		g_pGameSequence = new COGGameSequence ();
	}
	return g_pGameSequence;
}


IOGFPSCounter* GetFPSCounter ()
{
	if (g_pFPS == NULL)
	{
		g_pFPS = new COGFPSCounter ();
	}
	return g_pFPS;
}
