/*
 *  ogresourcemgr.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "OrangeGrass.h"
#include "ogresourcemgr.h"
#include "Pathes.h"


COGResourceMgr::COGResourceMgr ()
{
	char path[OG_MAX_PATH];
	GetResourcePathASCII(path, OG_MAX_PATH);
	m_ResPath = std::string(path) + std::string("GameResources");
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
}


// load from file.
bool COGResourceMgr::Init ()
{
	COGTexture* pLoadScr = new COGTexture ();
	pLoadScr->Init ("load_scr", m_ResPath + std::string("\\Textures\\UI\\load.pvr"));
	if (!pLoadScr->Load ())
	{
		OG_SAFE_DELETE(pLoadScr);
		return false;
	}
	m_TextureList["load_scr"] = pLoadScr;

	COGTexture* pLoadProgress = new COGTexture ();
	pLoadProgress->Init ("load_progress", m_ResPath + std::string("\\Textures\\UI\\load_progress.pvr"));
	if (!pLoadProgress->Load ())
	{
		OG_SAFE_DELETE(pLoadProgress);
		return false;
	}
	m_TextureList["load_progress"] = pLoadProgress;

	return true;
}


// get resource path
const std::string& COGResourceMgr::GetResourcePath () const
{
    return m_ResPath;
}


// load resources.
bool COGResourceMgr::Load (std::vector<IOGResourceInfo>& _resInfo)
{
	Cfg cfg;
	if (!LoadConfig(cfg))
	{
		return false;
	}

	std::vector<Cfg::ResourceCfg>::const_iterator iter;

	for (iter = cfg.texture_cfg_list.begin(); iter != cfg.texture_cfg_list.end(); ++iter)
	{
		COGTexture* pTexture = new COGTexture ();
		pTexture->Init ((*iter).alias, (*iter).file);
		m_TextureList[(*iter).alias] = pTexture;
		IOGResourceInfo inf;
		inf.m_Resource = (*iter).alias;
		inf.m_ResourceGroup = std::string("Textures");
		_resInfo.push_back(inf);
	}

	for (iter = cfg.mesh_cfg_list.begin(); iter != cfg.mesh_cfg_list.end(); ++iter)
	{
		COGMesh* pMesh = new COGMesh ();
		pMesh->Init ((*iter).alias, (*iter).file);
		m_MeshList[(*iter).alias] = pMesh;
		IOGResourceInfo inf;
		inf.m_Resource = (*iter).alias;
		inf.m_ResourceGroup = std::string("Meshes");
		_resInfo.push_back(inf);
	}

	for (iter = cfg.model_cfg_list.begin(); iter != cfg.model_cfg_list.end(); ++iter)
	{
		COGModel* pModel = new COGModel ();
		pModel->Init ((*iter).alias, (*iter).file);
		m_ModelList[(*iter).alias] = pModel;
		IOGResourceInfo inf;
		inf.m_Resource = (*iter).alias;
		inf.m_ResourceGroup = std::string("Models");
		inf.m_ResourceIcon = (*iter).icon;
		inf.m_ResourceActorType = (*iter).actor_type;
		_resInfo.push_back(inf);
	}

	for (iter = cfg.terrain_cfg_list.begin(); iter != cfg.terrain_cfg_list.end(); ++iter)
	{
		COGTerrain* pTerrain = new COGTerrain ();
		pTerrain->Init ((*iter).alias, (*iter).file);
		m_TerrainList[(*iter).alias] = pTerrain;
		IOGResourceInfo inf;
		inf.m_Resource = (*iter).alias;
		inf.m_ResourceGroup = std::string("Terrains");
		inf.m_ResourceIcon = (*iter).icon;
		_resInfo.push_back(inf);
	}

	return true;
}


// Load resource manager configuration
bool COGResourceMgr::LoadConfig (COGResourceMgr::Cfg& _cfg)
{
	int index = 0;
	std::string file_path;
	file_path = GetResourceMgr()->GetResourcePath() + std::string("\\resources.xml");

    TiXmlDocument* pXmlSettings = new TiXmlDocument ("resources.xml");
	if (!pXmlSettings->LoadFile (file_path.c_str()))
	{
		OG_SAFE_DELETE(pXmlSettings);
        return false;
	}
    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

	TiXmlHandle hTexturesRoot = hDoc->FirstChild ( "Textures" );
	index = 0;
	TiXmlHandle TextureHandle = hTexturesRoot.Child ( "Texture", index );
	while (TextureHandle.Node ())
	{
		TiXmlElement* pElement = TextureHandle.Element();

		Cfg::ResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		_cfg.texture_cfg_list.push_back(rescfg);

		TextureHandle = hTexturesRoot.Child ( "Texture", ++index );
	}

	TiXmlHandle hMeshesRoot = hDoc->FirstChild ( "Meshes" );
	index = 0;
	TiXmlHandle MeshHandle = hMeshesRoot.Child ( "Mesh", index );
	while (MeshHandle.Node ())
	{
		TiXmlElement* pElement = MeshHandle.Element();

		Cfg::ResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		_cfg.mesh_cfg_list.push_back(rescfg);

		MeshHandle = hMeshesRoot.Child ( "Mesh", ++index );
	}

	TiXmlHandle hModelsRoot = hDoc->FirstChild ( "Models" );
	index = 0;
	TiXmlHandle ModelHandle = hModelsRoot.Child ( "Model", index );
	while (ModelHandle.Node ())
	{
		TiXmlElement* pElement = ModelHandle.Element();

		Cfg::ResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.actor_type = std::string(pElement->Attribute ("actor_type"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		rescfg.icon = m_ResPath + std::string("\\") + std::string(pElement->Attribute ("icon"));
		_cfg.model_cfg_list.push_back(rescfg);

		ModelHandle = hModelsRoot.Child ( "Model", ++index );
	}

	TiXmlHandle hTerrainsRoot = hDoc->FirstChild ( "Terrains" );
	index = 0;
	TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Terrain", index );
	while (TerrainHandle.Node ())
	{
		TiXmlElement* pElement = TerrainHandle.Element();

		Cfg::ResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		rescfg.icon = m_ResPath + std::string("\\") + std::string(pElement->Attribute ("icon"));
		_cfg.terrain_cfg_list.push_back(rescfg);

		TerrainHandle = hTerrainsRoot.Child ( "Terrain", ++index );
	}

	OG_SAFE_DELETE(hDoc);
	OG_SAFE_DELETE(pXmlSettings);
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
				if (pTexture->Load() == NULL)
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
				if (pMesh->Load() == NULL)
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
				if (pModel->Load() == NULL)
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
				if (pTerrain->Load() == NULL)
					return NULL;
				return pTerrain;

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
