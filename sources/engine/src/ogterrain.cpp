/*
 *  ogterrain.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogterrain.h"


COGTerrain::COGTerrain () :	m_pMesh(NULL),
                            m_pMaterial(NULL),
							m_pTexture(NULL),
							m_Blend(OG_BLEND_NO)
{
    m_pRenderer = GetRenderer();
	m_pReader = GetSettingsReader();
	m_pGlobalVars = GetGlobalVars();
}


COGTerrain::~COGTerrain()
{
}


// Load terrain.
bool COGTerrain::Load ()
{
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;
            
    case OG_RESSTATE_DEFINED:
        break;
	}

	Cfg cfg;
	if (!LoadConfig(cfg))
	{
		return false;
	}

	m_pMesh = new COGSceneMesh ();
	m_pMesh->Init(std::string(""), cfg.mesh_file, m_ResourcePool);
	if (!m_pMesh->Load())
		return false;

	m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, cfg.texture_alias);

    m_pMaterial = m_pRenderer->CreateMaterial();
    m_pMaterial->SetAmbient(cfg.material_ambient);
    m_pMaterial->SetDiffuse(cfg.material_diffuse);
    m_pMaterial->SetSpecular(cfg.material_specular);
	m_Blend = OG_BLEND_SOLID;

	m_LoadState = OG_RESSTATE_LOADED;
	return true;
}


// Load terrain configuration
bool COGTerrain::LoadConfig (COGTerrain::Cfg& _cfg)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(m_ResourceFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load terrain config file %s", m_ResourceFile.c_str());
		return false;
	}

	IOGGroupNode* pMeshNode = m_pReader->OpenGroupNode(pSource, NULL, "Mesh");
	if (pMeshNode != NULL)
	{
		_cfg.mesh_file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pMeshNode, "file"));
		m_pReader->CloseGroupNode(pMeshNode);
	}

	IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, NULL, "Material");
	if (pMaterialNode != NULL)
	{
		_cfg.texture_alias = m_pReader->ReadStringParam(pMaterialNode, "texture");
		_cfg.blend_type = ParseBlendType(m_pReader->ReadStringParam(pMaterialNode, "blend"));
    	IOGGroupNode* pAmbientNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Ambient");
        if (pAmbientNode)
        {
            _cfg.material_ambient = m_pReader->ReadVec4Param(pAmbientNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pAmbientNode);
        }
    	IOGGroupNode* pDiffuseNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Diffuse");
        if (pDiffuseNode)
        {
            _cfg.material_diffuse = m_pReader->ReadVec4Param(pDiffuseNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pDiffuseNode);
        }
    	IOGGroupNode* pSpecularNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Specular");
        if (pSpecularNode)
        {
            _cfg.material_specular = m_pReader->ReadVec4Param(pSpecularNode, "r", "g", "b", "a");
    		m_pReader->CloseGroupNode(pSpecularNode);
        }

		m_pReader->CloseGroupNode(pMaterialNode);
	}

	m_pReader->CloseSource(pSource);
	return true;
}


// Save params
bool COGTerrain::SaveParams ()
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(m_ResourceFile);
	if (!pSource)
	{
		OG_LOG_ERROR("Failed to load terrain config file %s", m_ResourceFile.c_str());
		return false;
	}

	IOGGroupNode* pMaterialNode = m_pReader->OpenGroupNode(pSource, NULL, "Material");
	if (pMaterialNode != NULL)
	{
    	IOGGroupNode* pAmbientNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Ambient");
        if (pAmbientNode)
        {
            m_pReader->WriteVec4Param(pAmbientNode, "r", "g", "b", "a", m_pMaterial->GetAmbient());
    		m_pReader->CloseGroupNode(pAmbientNode);
        }
    	IOGGroupNode* pDiffuseNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Diffuse");
        if (pDiffuseNode)
        {
            m_pReader->WriteVec4Param(pDiffuseNode, "r", "g", "b", "a", m_pMaterial->GetDiffuse());
    		m_pReader->CloseGroupNode(pDiffuseNode);
        }
    	IOGGroupNode* pSpecularNode = m_pReader->OpenGroupNode(pSource, pMaterialNode, "Specular");
        if (pSpecularNode)
        {
            m_pReader->WriteVec4Param(pSpecularNode, "r", "g", "b", "a", m_pMaterial->GetSpecular());
    		m_pReader->CloseGroupNode(pSpecularNode);
        }
    }

    m_pReader->SaveSource(pSource, m_ResourceFile);
	return true;
}


// Unload terrain.
void COGTerrain::Unload ()
{
	if (m_LoadState != OG_RESSTATE_LOADED)
	{
		return;
	}

	if (m_pMesh)
	{
		m_pMesh->Unload();
		OG_SAFE_DELETE(m_pMesh);
	}

	m_Blend = OG_BLEND_NO;
	OG_SAFE_DELETE(m_pMaterial);

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render terrain.
void COGTerrain::Render (const OGMatrix& _mWorld)
{
	const IOGFrustum& frustum = m_pRenderer->GetCamera()->GetFrustum();

    m_pRenderer->SetMaterial(m_pMaterial);
    m_pRenderer->SetTexture(m_pTexture);
	m_pRenderer->SetBlend(OG_BLEND_SOLID);
	m_pMesh->RenderParts(frustum);
}


// Render all.
void COGTerrain::RenderAll (const OGMatrix& _mWorld)
{
	Render(_mWorld);
}


// Get ray intersection
bool COGTerrain::GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos)
{
    if (m_pMesh)
    {
        return m_pMesh->GetRayIntersection(_vRayPos, _vRayDir, _pOutPos);
    }
    return false;
}


// Get combined AABB
const IOGAabb& COGTerrain::GetAABB () const
{
	return m_pMesh->GetAABB();
}


// Get all submesh AABBs
void COGTerrain::GetAllAABBs (std::vector<IOGAabb*>& _aabbs) 
{
    _aabbs.clear();

    const std::vector<OGSubMesh>& subMeshes = m_pMesh->GetSubMeshes();
    std::vector<OGSubMesh>::const_iterator it = subMeshes.begin();
    for (; it != subMeshes.end(); ++it)
        _aabbs.push_back(it->aabb);
}
