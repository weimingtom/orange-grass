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
#include "IOGShaderManager.h"
#include "IOGResourceFile.h"
#include "IOGInputDispatcher.h"
#include "IOGRenderer.h"
#include "IOGStatistics.h"
#include "IOGEffectsManager.h"
#include "IOGGlobalVarsTable.h"
#include "IOGSettingsReader.h"
#include "IOGFPSCounter.h"
#include "IOGTerrain.h"
#include "common.h"

#include "IOGVector.h"
#include "IOGMatrix.h"
#include "IOGQuaternion.h"


void StartOrangeGrass(const std::string& _ResourcePath, bool _bSingleStorage);
void FinishOrangeGrass();

IOGResourceMgr* GetResourceMgr ();
IOGInputDispatcher* GetInput ();
IOGRenderer* GetRenderer ();
IOGShaderManager* GetShaderManager ();
IOGStatistics* GetStatistics ();
IOGEffectsManager* GetEffectsManager ();
IOGGlobalVarsTable* GetGlobalVars ();
IOGSettingsReader* GetSettingsReader ();
IOGFPSCounter* GetFPSCounter ();


IOGResourceFile* CreateResourceFile ();
void DestroyResourceFile (IOGResourceFile* _pFile);

IOGTerrain* CreateTerrain (const std::string& _TerrainFile);
void DestroyTerrain (IOGTerrain* _pTerrain);


// Parse the blend type string and convert it to internal type
OGBlendType ParseBlendType (const std::string& _BlendTypeStr);

// Parse the shader id string and convert it to internal type
OGShaderID ParseShaderId (const std::string& _ShaderIdStr);

// Parse the submesh type string and convert it to internal type
SubMeshType ParseSubMeshType (const std::string& _SubMeshTypeStr);

#endif