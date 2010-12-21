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
#include "ogrenderer_gles11.h"
#include "ogrenderer_gles20.h"
#include "ogspritepool.h"
#include "ogstatistics.h"
#include "ogeffectsmanager.h"
#include "ogactorparamsmgr.h"
#include "ogglobalvarstable.h"
#include "ogsettingsreader.h"
#include "ogappsettings.h"
#include "oggamesequence.h"
#include "ogluavm.h"


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
static IOGLuaVM* g_pLuaVM = NULL;


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
#ifdef GLES11
		g_pRenderer = new COGRenderer_GLES11 ();
#else
		g_pRenderer = new COGRenderer_GLES20 ();
#endif
		g_pRenderer->Init();
	}
	return g_pRenderer;
}


IOGRenderer* GetRendererGL11 ()
{
	if (g_pRenderer == NULL)
	{
		g_pRenderer = new COGRenderer_GLES11 ();
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


IOGLuaVM* GetLuaVM ()
{
	if (g_pLuaVM == NULL)
	{
		g_pLuaVM = new COGLuaVM ();
	}
	return g_pLuaVM;
}
