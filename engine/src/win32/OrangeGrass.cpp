#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "oglevelmanager.h"
#include "ogscenegraph.h"
#include "ogcamera.h"
#include "ogsprite.h"


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGLevelManager* g_pLevelMgr = NULL;
static IOGSceneGraph* g_pSg = NULL;
static IOGCamera* g_pCamera = NULL;


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


IOGCamera* GetCamera ()
{
	if (g_pCamera == NULL)
	{
		g_pCamera = new COGCamera ();
	}
	return g_pCamera;
}

IOGSprite* CreateSprite (const char* _pAlias)
{
	COGSprite* pSpr = new COGSprite ();
	pSpr->Init (GetResourceMgr()->GetTexture(_pAlias));
	return pSpr;
}
