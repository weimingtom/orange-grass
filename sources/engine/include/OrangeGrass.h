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
#include "IOGModel.h"
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

IOGModel* CreateTerrain (const std::string& _TerrainFile);
void DestroyTerrain (IOGModel* _pTerrain);


// Parse the blend type string and convert it to internal type
OGBlendType ParseBlendType (const std::string& _BlendTypeStr);

// Parse the shader id string and convert it to internal type
OGShaderID ParseShaderId (const std::string& _ShaderIdStr);

// Parse the submesh type string and convert it to internal type
SubMeshType ParseSubMeshType (const std::string& _SubMeshTypeStr);

#endif
