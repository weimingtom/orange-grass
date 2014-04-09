/*
 *  ogmodelconfig.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 18.06.13.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogmodelconfig.h"


COGModelConfig::COGModelConfig() 
    : m_pAnimationCfg (NULL)
    , m_pModelCfg(NULL)
{
    m_pReader = GetSettingsReader();
}


COGModelConfig::~COGModelConfig()
{
    OG_SAFE_DELETE (m_pAnimationCfg);
    OG_SAFE_DELETE (m_pModelCfg);
}


// Load model configuration
bool COGModelConfig::LoadConfig (const std::string& _ConfigFile)
{
    IOGSettingsSource* pSource = m_pReader->OpenSource(_ConfigFile);
    if (!pSource)
    {
        //OG_LOG_ERROR("Failed to load model config file %s", _ConfigFile.c_str());
        return false;
    }
    m_ConfigFile = _ConfigFile;

    // delete old configs
    OG_SAFE_DELETE (m_pAnimationCfg);
    OG_SAFE_DELETE (m_pModelCfg);

    IOGGroupNode* pModelNode = m_pReader->OpenGroupNode(pSource, NULL, "Model");
    if (pModelNode != NULL)
    {
        m_pModelCfg = new OGModelCfg;
        m_pModelCfg->model_file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pModelNode, "file"));

        IOGGroupNode* pMeshNode = m_pReader->OpenGroupNode(pSource, pModelNode, "Mesh");
        while (pMeshNode != NULL)
        {
            OGMeshCfg meshCfg;
            meshCfg.sceneprops = 0;

            meshCfg.shaderID = ParseShaderId(m_pReader->ReadStringParam(pMeshNode, "shader"));
            meshCfg.shadowShaderID = ParseShaderId(m_pReader->ReadStringParam(pMeshNode, "shadowshader"));
            meshCfg.sceneprops = (m_pReader->ReadIntParam(pMeshNode, "shadowcaster") == 0) ? meshCfg.sceneprops : (meshCfg.sceneprops | OG_SCENEPROP_SHADOWCASTER);
            meshCfg.sceneprops = (m_pReader->ReadIntParam(pMeshNode, "shadowreceiver") == 0) ? meshCfg.sceneprops : (meshCfg.sceneprops | OG_SCENEPROP_SHADOWRECEIVER);

            IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, pMeshNode, "Material");
            if (pMaterialNode != NULL)
            {
                meshCfg.material_cfg.texture_alias = m_pReader->ReadStringParam(pMaterialNode, "texture");
                meshCfg.material_cfg.blend_type = ParseBlendType(m_pReader->ReadStringParam(pMaterialNode, "blend"));
                IOGGroupNode* pAmbientNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Ambient");
                if (pAmbientNode)
                {
                    meshCfg.material_cfg.material_ambient = m_pReader->ReadVec4Param(pAmbientNode, "r", "g", "b", "a");
                    m_pReader->CloseGroupNode(pAmbientNode);
                }
                IOGGroupNode* pDiffuseNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Diffuse");
                if (pDiffuseNode)
                {
                    meshCfg.material_cfg.material_diffuse = m_pReader->ReadVec4Param(pDiffuseNode, "r", "g", "b", "a");
                    m_pReader->CloseGroupNode(pDiffuseNode);
                }
                IOGGroupNode* pSpecularNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Specular");
                if (pSpecularNode)
                {
                    meshCfg.material_cfg.material_specular = m_pReader->ReadVec4Param(pSpecularNode, "r", "g", "b", "a");
                    m_pReader->CloseGroupNode(pSpecularNode);
                }
                m_pReader->CloseGroupNode(pMaterialNode);
            }
            m_pModelCfg->mesh_cfg.push_back(meshCfg);
            pMeshNode = m_pReader->ReadNextNode(pMeshNode);
        }
        m_pReader->CloseGroupNode(pMeshNode);
    }
    m_pReader->CloseGroupNode(pModelNode);

    IOGGroupNode* pAnimationsNode = m_pReader->OpenGroupNode(pSource, NULL, "Animations");
    if (pAnimationsNode)
    {
        m_pAnimationCfg = new OGAnimationCfg;
        IOGGroupNode* pAnimationNode = m_pReader->OpenGroupNode(pSource, pAnimationsNode, "Animation");
        while (pAnimationNode != NULL)
        {
            IOGAnimation anim;
            anim.name = m_pReader->ReadStringParam(pAnimationNode, "name");
            anim.start_frame = (unsigned int)m_pReader->ReadIntParam(pAnimationNode, "start_frame");
            anim.end_frame = (unsigned int)m_pReader->ReadIntParam(pAnimationNode, "end_frame");
            anim.speed = (unsigned int)m_pReader->ReadIntParam(pAnimationNode, "speed");
            anim.looped = m_pReader->ReadIntParam(pAnimationNode, "looped") ? true : false;
            m_pAnimationCfg->anim_list[anim.name] = anim;
            pAnimationNode = m_pReader->ReadNextNode(pAnimationNode);
        }
        m_pReader->CloseGroupNode(pAnimationsNode);
    }

    m_pReader->CloseSource(pSource);
    return true;
}


// Save params
bool COGModelConfig::SaveConfig ()
{
    // TODO: implement
    return true;
}


// Get animation config
OGAnimationCfg* COGModelConfig::GetAnimationConfig ()
{
    return m_pAnimationCfg;
}


// Get model config
OGModelCfg* COGModelConfig::GetModelConfig ()
{
    return m_pModelCfg;
}


// Update animation config
void COGModelConfig::UpdateAnimationConfig (const OGAnimationCfg& _cfg)
{
    if (!m_pAnimationCfg)
    {
        m_pAnimationCfg = new OGAnimationCfg;
    }
    *m_pAnimationCfg = _cfg;
}


// Update model config
void COGModelConfig::UpdateModelConfig (const OGModelCfg& _cfg)
{
    if (!m_pModelCfg)
    {
        m_pModelCfg = new OGModelCfg;
    }
    *m_pModelCfg = _cfg;
}
