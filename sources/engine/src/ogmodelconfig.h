/*
 *  ogmodelconfig.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMODELCONFIG_H_
#define OGMODELCONFIG_H_

#include "IOGRenderTypes.h"
#include "IOGMath.h"
#include <list>
#include <string>
#include "IOGSettingsReader.h"
#include "IOGMaterial.h"
#include "IOGAnimation.h"
#include "IOGMesh.h"


class COGModelConfig
{
public:
    COGModelConfig();
    ~COGModelConfig();

	// Load model configuration
	bool LoadConfig (const std::string& _ConfigFile);

	// Save params
	bool SaveConfig ();

    // Get material config
    OGMaterialCfg* GetMaterialConfig ();

    // Get animation config
    OGAnimationCfg* GetAnimationConfig ();

    // Get mesh config
    OGMeshCfg* GetMeshConfig ();

    // Update material config
    void UpdateMaterialConfig (const OGMaterialCfg& _cfg);

    // Update animation config
    void UpdateAnimationConfig (const OGAnimationCfg& _cfg);

    // Update mesh config
    void UpdateMeshConfig (const OGMeshCfg& _cfg);

private:
	IOGSettingsReader*	m_pReader;
    std::string         m_ConfigFile;

    OGMaterialCfg*      m_pMaterialCfg;
    OGAnimationCfg*     m_pAnimationCfg;
    OGMeshCfg*          m_pMeshCfg;
};


#endif