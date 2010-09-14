/*
 *  OrangeGrass.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "oglevelmanager.h"
#include "ogscenegraph.h"
#include "ogactormanager.h"
#include "ogphysics.h"
#include "oginputdispatcher.h"
#include "ogrenderer.h"
#include "ogspritepool.h"
#include "ogmaterialmanager.h"
#include "ogstatistics.h"
#include "ogeffectsmanager.h"


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGLevelManager* g_pLevelMgr = NULL;
static IOGSceneGraph* g_pSg = NULL;
static IOGActorManager* g_pActorMgr = NULL;
static IOGPhysics* g_pPhysics = NULL;
static IOGInputDispatcher* g_pInput = NULL;
static IOGRenderer* g_pRenderer = NULL;
static IOGMaterialManager* g_pMaterialMgr = NULL;
static IOGStatistics* g_pStats = NULL;
static IOGSpritePool* g_pSprPool = NULL;
static IOGEffectsManager* g_pEffectsMgr = NULL;


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


IOGMaterialManager* GetMaterialManager ()
{
	if (g_pMaterialMgr == NULL)
	{
		g_pMaterialMgr = new COGMaterialManager ();
	}
	return g_pMaterialMgr;
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
