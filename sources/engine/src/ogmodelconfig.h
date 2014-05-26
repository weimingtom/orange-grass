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