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
#include "oginputdispatcher.h"
#include "ogrenderer.h"
#include "ogstatistics.h"
#include "ogeffectsmanager.h"
#include "ogglobalvarstable.h"
#include "ogsettingsreader.h"
#include "ogfpscounter.h"
#include "ogresourcefile.h"
#include "ogterrain.h"
#include <map>


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGInputDispatcher* g_pInput = NULL;
static IOGRenderer* g_pRenderer = NULL;
static IOGStatistics* g_pStats = NULL;
static IOGEffectsManager* g_pEffectsMgr = NULL;
static IOGGlobalVarsTable* g_pGlobalVars = NULL;
static IOGSettingsReader* g_pSettingsReader = NULL;
static IOGFPSCounter* g_pFPS = NULL;

static std::map<std::string, OGBlendType> g_BlendTypeLookup;


void StartOrangeGrass(const std::string& _ResourcePath, bool _bSingleStorage)
{
	g_BlendTypeLookup["solid"] = OG_BLEND_SOLID;
	g_BlendTypeLookup["test"] = OG_BLEND_ALPHATEST;
	g_BlendTypeLookup["blend"] = OG_BLEND_ALPHABLEND;
	g_BlendTypeLookup["add"] = OG_BLEND_ALPHAADD;

    InitializeResourceSystem(_ResourcePath, _bSingleStorage);
}


void FinishOrangeGrass()
{
	g_BlendTypeLookup.clear();

    ShutdownResourceSystem();

    OG_SAFE_DELETE(g_pRenderer);
    OG_SAFE_DELETE(g_pResourceMgr);
    OG_SAFE_DELETE(g_pInput);
    OG_SAFE_DELETE(g_pEffectsMgr);
    OG_SAFE_DELETE(g_pGlobalVars);
    OG_SAFE_DELETE(g_pSettingsReader);
    OG_SAFE_DELETE(g_pStats);
    OG_SAFE_DELETE(g_pFPS);
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


IOGEffectsManager* GetEffectsManager ()
{
	if (g_pEffectsMgr == NULL)
	{
		g_pEffectsMgr = new COGEffectsManager ();
	}
	return g_pEffectsMgr;
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


IOGFPSCounter* GetFPSCounter ()
{
	if (g_pFPS == NULL)
	{
		g_pFPS = new COGFPSCounter ();
	}
	return g_pFPS;
}


IOGResourceFile* CreateResourceFile ()
{
    COGResourceFile *pFile = new COGResourceFile();
    return pFile;
}


void DestroyResourceFile (IOGResourceFile* _pFile)
{
    OG_SAFE_DELETE(_pFile);
}


IOGTerrain* CreateTerrain (const std::string& _TerrainFile)
{
    COGTerrain* pTerrain = new COGTerrain();
	pTerrain->Init(std::string(""), _TerrainFile, OG_RESPOOL_GAME);
	if (!pTerrain->Load())
    {
        OG_LOG_ERROR("Failed to load terrain from %s", _TerrainFile.c_str());
        OG_SAFE_DELETE(pTerrain);
        return NULL;
    }
    return pTerrain;
}


void DestroyTerrain (IOGTerrain* _pTerrain)
{
	if (_pTerrain)
	{
		((COGTerrain*)_pTerrain)->Unload();
		OG_SAFE_DELETE(_pTerrain);
	}
}
