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
#include "IOGModel.h"


class COGModelConfig
{
public:
    COGModelConfig();
    ~COGModelConfig();

    // Load model configuration
    bool LoadConfig (const std::string& _ConfigFile);

    // Save params
    bool SaveConfig ();

    // Get animation config
    OGAnimationCfg* GetAnimationConfig ();

    // Get model config
    OGModelCfg* GetModelConfig ();

    // Update animation config
    void UpdateAnimationConfig (const OGAnimationCfg& _cfg);

    // Update model config
    void UpdateModelConfig (const OGModelCfg& _cfg);

private:
    IOGSettingsReader*  m_pReader;
    std::string         m_ConfigFile;

    OGAnimationCfg*     m_pAnimationCfg;
    OGModelCfg*         m_pModelCfg;
};


#endif