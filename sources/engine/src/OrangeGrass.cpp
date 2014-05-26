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
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "oginputdispatcher.h"
#include "ogrenderer.h"
#include "ogshadermanager.h"
#include "ogstatistics.h"
#include "ogeffectsmanager.h"
#include "ogglobalvarstable.h"
#include "ogsettingsreader.h"
#include "ogfpscounter.h"
#include "ogresourcefile.h"
#include "ogmodel.h"
#include <map>


static IOGResourceMgr* g_pResourceMgr = NULL;
static IOGInputDispatcher* g_pInput = NULL;
static IOGRenderer* g_pRenderer = NULL;
static IOGShaderManager* g_pShaderManager = NULL;
static IOGStatistics* g_pStats = NULL;
static IOGEffectsManager* g_pEffectsMgr = NULL;
static IOGGlobalVarsTable* g_pGlobalVars = NULL;
static IOGSettingsReader* g_pSettingsReader = NULL;
static IOGFPSCounter* g_pFPS = NULL;

static std::map<std::string, OGBlendType> g_BlendTypeLookup;
static std::map<std::string, OGShaderID> g_ShaderIdLookup;
static std::map<std::string, SubMeshType> g_SubMeshTypeLookup;


void StartOrangeGrass(const std::string& _ResourcePath, bool _bSingleStorage)
{
    g_BlendTypeLookup["solid"] = OG_BLEND_SOLID;
    g_BlendTypeLookup["test"] = OG_BLEND_ALPHATEST;
    g_BlendTypeLookup["blend"] = OG_BLEND_ALPHABLEND;
    g_BlendTypeLookup["add"] = OG_BLEND_ALPHAADD;

    g_ShaderIdLookup["coloreffect"] = OG_SHADER_COLOREFFECT;
    g_ShaderIdLookup["model"] = OG_SHADER_MODEL;
    g_ShaderIdLookup["transparentmodel"] = OG_SHADER_TRANSPARENTMODEL;
    g_ShaderIdLookup["shadowedscene"] = OG_SHADER_SHADOWEDSCENE;
    g_ShaderIdLookup["shadowedtransparentscene"] = OG_SHADER_SHADOWEDTRANSPARENTSCENE;
    g_ShaderIdLookup["shadowmodel"] = OG_SHADER_SHADOWMODEL;
    g_ShaderIdLookup["shadowtransparentmodel"] = OG_SHADER_SHADOWTRANSPARENTMODEL;
    g_ShaderIdLookup["sprite"] = OG_SHADER_SPRITE;
    g_ShaderIdLookup["text"] = OG_SHADER_TEXT;

    g_SubMeshTypeLookup["propeller"] = OG_SUBMESH_PROPELLER;
    g_SubMeshTypeLookup["actpointweapon01"] = OG_SUBMESH_ACTPOINT;
    g_SubMeshTypeLookup["actpointweapon02"] = OG_SUBMESH_ACTPOINT;

    InitializeResourceSystem(_ResourcePath, _bSingleStorage);
}


void FinishOrangeGrass()
{
    g_BlendTypeLookup.clear();
    g_ShaderIdLookup.clear();
    g_SubMeshTypeLookup.clear();

    ShutdownResourceSystem();

    OG_SAFE_DELETE(g_pRenderer);
    OG_SAFE_DELETE(g_pShaderManager);
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


// Parse the shader id string and convert it to internal type
OGShaderID ParseShaderId (const std::string& _ShaderIdStr)
{
    std::map<std::string, OGShaderID>::const_iterator iter = g_ShaderIdLookup.find(_ShaderIdStr);
    if (iter != g_ShaderIdLookup.end())
    {
        return iter->second;
    }
    return OG_SHADER_NO;
}


// Parse the submesh type string and convert it to internal type
SubMeshType ParseSubMeshType (const std::string& _SubMeshTypeStr)
{
    std::map<std::string, SubMeshType>::const_iterator iter = g_SubMeshTypeLookup.find(_SubMeshTypeStr);
    if (iter != g_SubMeshTypeLookup.end())
    {
        return iter->second;
    }
    return OG_SUBMESH_BODY;
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


IOGShaderManager* GetShaderManager ()
{
    if (g_pShaderManager == NULL)
    {
        g_pShaderManager = new COGShaderManager ();
    }
    return g_pShaderManager;
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


IOGModel* CreateTerrain (const std::string& _TerrainFile)
{
    COGModel* pTerrain = new COGModel();
    pTerrain->Init(std::string(""), _TerrainFile, OG_RESPOOL_GAME);
    if (!pTerrain->Load())
    {
        OG_LOG_ERROR("Failed to load terrain from %s", _TerrainFile.c_str());
        OG_SAFE_DELETE(pTerrain);
        return NULL;
    }
    return pTerrain;
}


void DestroyTerrain (IOGModel* _pTerrain)
{
    if (_pTerrain)
    {
        ((COGModel*)_pTerrain)->Unload();
        OG_SAFE_DELETE(_pTerrain);
    }
}
