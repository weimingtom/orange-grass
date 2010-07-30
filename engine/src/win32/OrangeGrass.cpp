#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "oglevelmanager.h"
#include "ogscenegraph.h"
#include "ogactormanager.h"
#include "ogcamera.h"
#include "oglight.h"
#include "ogsprite.h"


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGLevelManager* g_pLevelMgr = NULL;
static IOGSceneGraph* g_pSg = NULL;
static IOGActorManager* g_pActorMgr = NULL;
static IOGCamera* g_pCamera = NULL;
static IOGLight* g_pLight = NULL;


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


IOGCamera* GetCamera ()
{
	if (g_pCamera == NULL)
	{
		g_pCamera = new COGCamera ();
	}
	return g_pCamera;
}


IOGLight* GetLight ()
{
	if (g_pLight == NULL)
	{
		g_pLight = new COGLight ();
	}
	return g_pLight;
}


IOGSprite* CreateSprite (const char* _pAlias)
{
	COGSprite* pSpr = new COGSprite ();
	pSpr->Init (GetResourceMgr()->GetTexture(_pAlias));
	return pSpr;
}
