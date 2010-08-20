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
#include "ogsprite.h"


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGLevelManager* g_pLevelMgr = NULL;
static IOGSceneGraph* g_pSg = NULL;
static IOGActorManager* g_pActorMgr = NULL;
static IOGPhysics* g_pPhysics = NULL;
static IOGInputDispatcher* g_pInput = NULL;


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


IOGSprite* CreateSprite (const std::string& _Alias)
{
	COGSprite* pSpr = new COGSprite ();
	pSpr->Init (GetResourceMgr()->GetTexture(_Alias));
	return pSpr;
}
