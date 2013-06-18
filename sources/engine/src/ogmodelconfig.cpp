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


COGModelConfig::COGModelConfig() :
    m_pMaterialCfg (NULL),
    m_pAnimationCfg (NULL),
    m_pMeshCfg (NULL)
{
	m_pReader = GetSettingsReader();
}


COGModelConfig::~COGModelConfig()
{
    OG_SAFE_DELETE (m_pMaterialCfg);
    OG_SAFE_DELETE (m_pAnimationCfg);
    OG_SAFE_DELETE (m_pMeshCfg);
}


// Load model configuration
bool COGModelConfig::LoadConfig (const std::string& _ConfigFile)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(_ConfigFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load model config file %s", _ConfigFile.c_str());
		return false;
	}
    m_ConfigFile = _ConfigFile;

    // delete old configs
    OG_SAFE_DELETE (m_pMaterialCfg);
    OG_SAFE_DELETE (m_pAnimationCfg);
    OG_SAFE_DELETE (m_pMeshCfg);

	IOGGroupNode* pMeshNode = m_pReader->OpenGroupNode(pSource, NULL, "Mesh");
	if (pMeshNode != NULL)
	{
        m_pMeshCfg = new OGMeshCfg;
		m_pMeshCfg->mesh_file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pMeshNode, "file"));
		m_pReader->CloseGroupNode(pMeshNode);
	}

	IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, NULL, "Material");
	if (pMaterialNode != NULL)
	{
        m_pMaterialCfg = new OGMaterialCfg;
		m_pMaterialCfg->texture_alias = m_pReader->ReadStringParam(pMaterialNode, "texture");
		m_pMaterialCfg->blend_type = ParseBlendType(m_pReader->ReadStringParam(pMaterialNode, "blend"));
    	IOGGroupNode* pAmbientNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Ambient");
        if (pAmbientNode)
        {
            m_pMaterialCfg->material_ambient = m_pReader->ReadVec4Param(pAmbientNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pAmbientNode);
        }
    	IOGGroupNode* pDiffuseNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Diffuse");
        if (pDiffuseNode)
        {
            m_pMaterialCfg->material_diffuse = m_pReader->ReadVec4Param(pDiffuseNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pDiffuseNode);
        }
    	IOGGroupNode* pSpecularNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Specular");
        if (pSpecularNode)
        {
            m_pMaterialCfg->material_specular = m_pReader->ReadVec4Param(pSpecularNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pSpecularNode);
        }
		m_pReader->CloseGroupNode(pMaterialNode);
	}

	IOGGroupNode* pAnimationsNode = m_pReader->OpenGroupNode(pSource, NULL, "Animations");
    if (pAnimationsNode)
    {
        m_pAnimationCfg = new OGAnimationCfg;
        IOGGroupNode* pAnimationNode = m_pReader->OpenGroupNode(pSource, pAnimationsNode, "Animation");
        while (pAnimationNode != NULL)
        {
            OGAnimationCfg::Anim anim;
            anim.anim_alias = m_pReader->ReadStringParam(pAnimationNode, "name");
            anim.anim_start = m_pReader->ReadIntParam(pAnimationNode, "start_frame");
            anim.anim_end = m_pReader->ReadIntParam(pAnimationNode, "end_frame");
            anim.speed = m_pReader->ReadIntParam(pAnimationNode, "speed");
            anim.looped = m_pReader->ReadIntParam(pAnimationNode, "looped");
            m_pAnimationCfg->anim_list.push_back(anim);
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
	IOGSettingsSource* pSource = m_pReader->OpenSource(m_ConfigFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load model config file %s", m_ConfigFile.c_str());
		return false;
	}

    if (m_pMaterialCfg)
    {
        IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, NULL, "Material");
        if (pMaterialNode != NULL)
        {
            IOGGroupNode* pAmbientNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Ambient");
            if (pAmbientNode)
            {
                m_pReader->WriteVec4Param(pAmbientNode, "r", "g", "b", "a", m_pMaterialCfg->material_ambient);
                m_pReader->CloseGroupNode(pAmbientNode);
            }
            IOGGroupNode* pDiffuseNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Diffuse");
            if (pDiffuseNode)
            {
                m_pReader->WriteVec4Param(pDiffuseNode, "r", "g", "b", "a", m_pMaterialCfg->material_diffuse);
                m_pReader->CloseGroupNode(pDiffuseNode);
            }
            IOGGroupNode* pSpecularNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Specular");
            if (pSpecularNode)
            {
                m_pReader->WriteVec4Param(pSpecularNode, "r", "g", "b", "a", m_pMaterialCfg->material_specular);
                m_pReader->CloseGroupNode(pSpecularNode);
            }
        }
    }

    if (!m_pReader->SaveSource(pSource, m_ConfigFile))
	{
		OG_LOG_ERROR("Failed to save model config file %s", m_ConfigFile.c_str());
		return false;
	}

	return true;
}


// Get material config
OGMaterialCfg* COGModelConfig::GetMaterialConfig ()
{
    return m_pMaterialCfg;
}


// Get animation config
OGAnimationCfg* COGModelConfig::GetAnimationConfig ()
{
    return m_pAnimationCfg;
}


// Get mesh config
OGMeshCfg* COGModelConfig::GetMeshConfig ()
{
    return m_pMeshCfg;
}


// Update material config
void COGModelConfig::UpdateMaterialConfig (const OGMaterialCfg& _cfg)
{
    if (!m_pMaterialCfg)
    {
        m_pMaterialCfg = new OGMaterialCfg;
    }
    *m_pMaterialCfg = _cfg;
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


// Update mesh config
void COGModelConfig::UpdateMeshConfig (const OGMeshCfg& _cfg)
{
    if (!m_pMeshCfg)
    {
        m_pMeshCfg = new OGMeshCfg;
    }
    *m_pMeshCfg = _cfg;
}
