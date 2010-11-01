/*
 *  ogresourcemgr.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "Pathes.h"


COGResourceMgr::COGResourceMgr ()
{
	char path[OG_MAX_PATH];
	GetResourcePathASCII(path, OG_MAX_PATH);
#ifndef WIN32
    m_ResPath = std::string(path) + std::string("/") + std::string("GameResources");
#else
	m_ResPath = std::string(path) + std::string("GameResources");
#endif
	m_pReader = GetSettingsReader();
}


COGResourceMgr::~COGResourceMgr ()
{
	std::map<std::string, COGTexture*>::iterator texture_iter = m_TextureList.begin();
	for( ; texture_iter != m_TextureList.end(); ++texture_iter )
	{
		OG_SAFE_DELETE (texture_iter->second);
	}

	std::map<std::string, COGMesh*>::iterator mesh_iter = m_MeshList.begin();
	for( ; mesh_iter != m_MeshList.end(); ++mesh_iter )
	{
		OG_SAFE_DELETE (mesh_iter->second);
	}
	
	std::map<std::string, COGModel*>::iterator model_iter = m_ModelList.begin();
	for( ; model_iter != m_ModelList.end(); ++model_iter )
	{
		OG_SAFE_DELETE (model_iter->second);
	}
	
	std::map<std::string, COGTerrain*>::iterator terra_iter = m_TerrainList.begin();
	for( ; terra_iter != m_TerrainList.end(); ++terra_iter )
	{
		OG_SAFE_DELETE (terra_iter->second);
	}
	
	std::map<std::string, COGSprite*>::iterator spr_iter = m_SpriteList.begin();
	for( ; spr_iter != m_SpriteList.end(); ++spr_iter )
	{
		OG_SAFE_DELETE (spr_iter->second);
	}
}


// load from file.
bool COGResourceMgr::Init ()
{
	GetMaterialManager()->Init();
	return true;
}


// get resource path
const std::string& COGResourceMgr::GetResourcePath () const
{
    return m_ResPath;
}


// get full resource path
std::string COGResourceMgr::GetFullPath (const std::string& _File) const
{
	return m_ResPath + std::string("/") + _File;
}


// load resources.
bool COGResourceMgr::Load ()
{
	Cfg cfg;
	if (!LoadConfig(cfg))
	{
		return false;
	}

	Cfg::TTextureCfg::const_iterator texiter;
	for (texiter = cfg.texture_cfg_list.begin(); texiter != cfg.texture_cfg_list.end(); ++texiter)
	{
		COGTexture* pTexture = new COGTexture ();
		pTexture->Init ((*texiter).alias, (*texiter).file);
		std::list<Cfg::TextureResourceCfg::MappingCfg>::const_iterator miter;
		for (miter = (*texiter).mappings.begin(); miter != (*texiter).mappings.end(); ++miter)
		{
			IOGMapping m;
			m.upper_left = (*miter).pos;
			m.size = (*miter).size;
			pTexture->AddMapping(&m);
		}

		m_TextureList[(*texiter).alias] = pTexture;
	}

	Cfg::TMeshCfg::const_iterator meshiter;
	for (meshiter = cfg.mesh_cfg_list.begin(); meshiter != cfg.mesh_cfg_list.end(); ++meshiter)
	{
		COGMesh* pMesh = new COGMesh ();
		pMesh->Init ((*meshiter).alias, (*meshiter).file);
		m_MeshList[(*meshiter).alias] = pMesh;
	}

	Cfg::TModelCfg::const_iterator modeliter;
	for (modeliter = cfg.model_cfg_list.begin(); modeliter != cfg.model_cfg_list.end(); ++modeliter)
	{
		COGModel* pModel = new COGModel ();
		pModel->Init ((*modeliter).alias, (*modeliter).file);
		m_ModelList[(*modeliter).alias] = pModel;
	}

	Cfg::TTerrainCfg::const_iterator terraiter;
	for (terraiter = cfg.terrain_cfg_list.begin(); terraiter != cfg.terrain_cfg_list.end(); ++terraiter)
	{
		COGTerrain* pTerrain = new COGTerrain ();
		pTerrain->Init ((*terraiter).alias, (*terraiter).file);
		m_TerrainList[(*terraiter).alias] = pTerrain;
	}

	Cfg::TSpriteCfg::const_iterator spriter;
	for (spriter = cfg.sprite_cfg_list.begin(); spriter != cfg.sprite_cfg_list.end(); ++spriter)
	{
		COGSprite* pSprite = new COGSprite ();
		pSprite->Init ((*spriter).alias, (*spriter).texture);
		pSprite->SetMapping((*spriter).mapping);
		m_SpriteList[(*spriter).alias] = pSprite;
	}

	return true;
}


// Load resource manager configuration
bool COGResourceMgr::LoadConfig (COGResourceMgr::Cfg& _cfg)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(GetFullPath("resources.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pTexturesRoot = m_pReader->OpenGroupNode(pSource, NULL, "Textures");
	if (pTexturesRoot)
	{
		IOGGroupNode* pTextureNode = m_pReader->OpenGroupNode(pSource, pTexturesRoot, "Texture");
		while (pTextureNode)
		{
			Cfg::TextureResourceCfg rescfg;
			rescfg.alias = m_pReader->ReadStringParam(pTextureNode, "alias");
			rescfg.file = GetFullPath(m_pReader->ReadStringParam(pTextureNode, "file"));

			IOGGroupNode* pMappingRoot = m_pReader->OpenGroupNode(pSource, pTextureNode, "Mappings");
			if (pMappingRoot)
			{
				IOGGroupNode* pMappingNode = m_pReader->OpenGroupNode(pSource, pMappingRoot, "Mapping");
				while (pMappingNode)
				{
					Cfg::TextureResourceCfg::MappingCfg mapcfg;
					mapcfg.pos = m_pReader->ReadVec2Param(pMappingNode, "x", "y");
					mapcfg.size = m_pReader->ReadVec2Param(pMappingNode, "width", "height");
					rescfg.mappings.push_back(mapcfg);

					pMappingNode = m_pReader->ReadNextNode(pMappingNode);
				}
				m_pReader->CloseGroupNode(pMappingRoot);
			}

			_cfg.texture_cfg_list.push_back(rescfg);
			pTextureNode = m_pReader->ReadNextNode(pTextureNode);
		}
		m_pReader->CloseGroupNode(pTexturesRoot);
	}

	IOGGroupNode* pMeshesRoot = m_pReader->OpenGroupNode(pSource, NULL, "Meshes");
	if (pMeshesRoot)
	{
		IOGGroupNode* pMeshNode = m_pReader->OpenGroupNode(pSource, pMeshesRoot, "Mesh");
		while (pMeshNode)
		{
			Cfg::MeshResourceCfg rescfg;
			rescfg.alias = m_pReader->ReadStringParam(pMeshNode, "alias");
			rescfg.file = GetFullPath(m_pReader->ReadStringParam(pMeshNode, "file"));
			_cfg.mesh_cfg_list.push_back(rescfg);

			pMeshNode = m_pReader->ReadNextNode(pMeshNode);
		}
		m_pReader->CloseGroupNode(pMeshesRoot);
	}

	IOGGroupNode* pModelsRoot = m_pReader->OpenGroupNode(pSource, NULL, "Models");
	if (pModelsRoot)
	{
		IOGGroupNode* pModelNode = m_pReader->OpenGroupNode(pSource, pModelsRoot, "Model");
		while (pModelNode)
		{
			Cfg::ModelResourceCfg rescfg;
			rescfg.alias = m_pReader->ReadStringParam(pModelNode, "alias");
			rescfg.file = GetFullPath(m_pReader->ReadStringParam(pModelNode, "file"));
			_cfg.model_cfg_list.push_back(rescfg);

			pModelNode = m_pReader->ReadNextNode(pModelNode);
		}
		m_pReader->CloseGroupNode(pModelsRoot);
	}

	IOGGroupNode* pTerrainsRoot = m_pReader->OpenGroupNode(pSource, NULL, "Terrains");
	if (pTerrainsRoot)
	{
		IOGGroupNode* pTerrainNode = m_pReader->OpenGroupNode(pSource, pTerrainsRoot, "Terrain");
		while (pTerrainNode)
		{
			Cfg::TerrainResourceCfg rescfg;
			rescfg.alias = m_pReader->ReadStringParam(pTerrainNode, "alias");
			rescfg.file = GetFullPath(m_pReader->ReadStringParam(pTerrainNode, "file"));
			_cfg.terrain_cfg_list.push_back(rescfg);

			pTerrainNode = m_pReader->ReadNextNode(pTerrainNode);
		}
		m_pReader->CloseGroupNode(pTerrainsRoot);
	}

	IOGGroupNode* pSpritesRoot = m_pReader->OpenGroupNode(pSource, NULL, "Sprites");
	if (pSpritesRoot)
	{
		IOGGroupNode* pSpriteNode = m_pReader->OpenGroupNode(pSource, pSpritesRoot, "Sprite");
		while (pSpriteNode)
		{
			Cfg::SpriteResourceCfg rescfg;
			rescfg.alias = m_pReader->ReadStringParam(pSpriteNode, "alias");
			rescfg.texture = m_pReader->ReadStringParam(pSpriteNode, "texture");
			rescfg.mapping = (unsigned int)m_pReader->ReadIntParam(pSpriteNode, "mapping");
			_cfg.sprite_cfg_list.push_back(rescfg);

			pSpriteNode = m_pReader->ReadNextNode(pSpriteNode);
		}
		m_pReader->CloseGroupNode(pSpritesRoot);
	}

	m_pReader->CloseSource(pSource);
	return true;
}


// get texture
IOGTexture* COGResourceMgr::GetTexture (const std::string& _Alias)
{
	COGTexture* pTexture = m_TextureList[_Alias];
    if (pTexture)
    {
		switch (pTexture->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
				return pTexture;

			case OG_RESSTATE_DEFINED:
				if (pTexture->Load() == false)
					return NULL;
				return pTexture;

			default:
				return NULL;
		}
    }
    return NULL;
}


// get mesh
IOGMesh* COGResourceMgr::GetMesh (const std::string& _Alias)
{
	COGMesh* pMesh = m_MeshList[_Alias];
    if (pMesh)
    {
		switch (pMesh->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
				return pMesh;

			case OG_RESSTATE_DEFINED:
				if (pMesh->Load() == false)
					return NULL;
				return pMesh;

			default:
				return NULL;
		}
    }
    return NULL;
}


// get model
IOGModel* COGResourceMgr::GetModel (const std::string& _Alias)
{
	COGModel* pModel = m_ModelList[_Alias];
    if (pModel)
    {
		switch (pModel->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
				return pModel;

			case OG_RESSTATE_DEFINED:
				if (pModel->Load() == false)
					return NULL;
				return pModel;

			default:
				return NULL;
		}
    }
    return NULL;
}


// get terrain.
IOGTerrain* COGResourceMgr::GetTerrain (const std::string& _Alias)
{
	COGTerrain* pTerrain = m_TerrainList[_Alias];
    if (pTerrain)
    {
		switch (pTerrain->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
				return pTerrain;

			case OG_RESSTATE_DEFINED:
				if (pTerrain->Load() == false)
					return NULL;
				return pTerrain;

			default:
				return NULL;
		}
    }
    return NULL;
}


// get sprite.
IOGSprite* COGResourceMgr::GetSprite (const std::string& _Alias)
{
	COGSprite* pSprite = m_SpriteList[_Alias];
    if (pSprite)
    {
		switch (pSprite->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
				return pSprite;

			case OG_RESSTATE_DEFINED:
				if (pSprite->Load() == false)
					return NULL;
				return pSprite;

			default:
				return NULL;
		}
    }
    return NULL;
}


// release texture.
void COGResourceMgr::ReleaseTexture (IOGTexture* _pTexture)
{
	COGTexture* pTexture = (COGTexture*)_pTexture;
	if (pTexture)
	{
		pTexture->Unload();
	}
}


// release mesh.
void COGResourceMgr::ReleaseMesh (IOGMesh* _pMesh)
{
	COGMesh* pMesh = (COGMesh*)_pMesh;
	if (pMesh)
	{
		pMesh->Unload();
	}
}


// release model.
void COGResourceMgr::ReleaseModel (IOGModel* _pModel)
{
	COGModel* pModel = (COGModel*)_pModel;
	if (pModel)
	{
		pModel->Unload();
	}
}


// release terrain.
void COGResourceMgr::ReleaseTerrain (IOGTerrain* _pTerrain)
{
	COGTerrain* pTerrain = (COGTerrain*)_pTerrain;
	if (pTerrain)
	{
		pTerrain->Unload();
	}
}


// release sprite.
void COGResourceMgr::ReleaseSprite (IOGSprite* _pSprite)
{
	COGSprite* pSprite = (COGSprite*)_pSprite;
	if (pSprite)
	{
		pSprite->Unload();
	}
}
