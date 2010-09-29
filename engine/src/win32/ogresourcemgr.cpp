/*
 *  ogresourcemgr.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
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
	COGTexture* pLoadScr = new COGTexture ();
	pLoadScr->Init ("load_scr", m_ResPath + std::string("/Textures/UI/load.pvr"));
	if (!pLoadScr->Load ())
	{
		OG_SAFE_DELETE(pLoadScr);
		return false;
	}
	m_TextureList["load_scr"] = pLoadScr;

	COGTexture* pLoadProgress = new COGTexture ();
	pLoadProgress->Init ("load_progress", m_ResPath + std::string("/Textures/UI/load_progress.pvr"));
	if (!pLoadProgress->Load ())
	{
		OG_SAFE_DELETE(pLoadProgress);
		return false;
	}
	m_TextureList["load_progress"] = pLoadProgress;

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
		pSprite->SetMapping((*spriter).pos, (*spriter).size);
		m_SpriteList[(*spriter).alias] = pSprite;
	}

	return true;
}


// Load resource manager configuration
bool COGResourceMgr::LoadConfig (COGResourceMgr::Cfg& _cfg)
{
	int index = 0;
	std::string file_path;
	file_path = m_ResPath + std::string("/resources.xml");

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
		Cfg::TextureResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));

		TiXmlHandle hMappingsRoot = TextureHandle.FirstChild ( "Mappings" );
		unsigned int mapindex = 0;
		TiXmlHandle MappingHandle = hMappingsRoot.Child ( "Mapping", mapindex );
		while (MappingHandle.Node ())
		{
			TiXmlElement* pMappingElement = MappingHandle.Element();
			int x, y, w, h;
			pMappingElement->Attribute("x", &x);
			pMappingElement->Attribute("y", &y);
			pMappingElement->Attribute("width", &w);
			pMappingElement->Attribute("height", &h);
			Cfg::TextureResourceCfg::MappingCfg mapcfg;
			mapcfg.pos = Vec2((float)x, (float)y);
			mapcfg.size = Vec2((float)w, (float)h);
			rescfg.mappings.push_back(mapcfg);
			MappingHandle = hMappingsRoot.Child ( "Mapping", ++mapindex );
		}

		_cfg.texture_cfg_list.push_back(rescfg);

		TextureHandle = hTexturesRoot.Child ( "Texture", ++index );
	}

	TiXmlHandle hMeshesRoot = hDoc->FirstChild ( "Meshes" );
	index = 0;
	TiXmlHandle MeshHandle = hMeshesRoot.Child ( "Mesh", index );
	while (MeshHandle.Node ())
	{
		TiXmlElement* pElement = MeshHandle.Element();

		Cfg::MeshResourceCfg rescfg;
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

		Cfg::ModelResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		_cfg.model_cfg_list.push_back(rescfg);

		ModelHandle = hModelsRoot.Child ( "Model", ++index );
	}

	TiXmlHandle hTerrainsRoot = hDoc->FirstChild ( "Terrains" );
	index = 0;
	TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Terrain", index );
	while (TerrainHandle.Node ())
	{
		TiXmlElement* pElement = TerrainHandle.Element();

		Cfg::TerrainResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.file = m_ResPath + std::string("/") + std::string(pElement->Attribute ("file"));
		_cfg.terrain_cfg_list.push_back(rescfg);

		TerrainHandle = hTerrainsRoot.Child ( "Terrain", ++index );
	}

	TiXmlHandle hSpritesRoot = hDoc->FirstChild ( "Sprites" );
	index = 0;
	TiXmlHandle SpriteHandle = hSpritesRoot.Child ( "Sprite", index );
	while (SpriteHandle.Node ())
	{
		TiXmlElement* pElement = SpriteHandle.Element();

		Cfg::SpriteResourceCfg rescfg;
		rescfg.alias = std::string(pElement->Attribute ("alias"));
		rescfg.texture = std::string(pElement->Attribute ("texture"));
		int x, y, w, h;
		pElement->Attribute("x", &x);
		pElement->Attribute("y", &y);
		pElement->Attribute("width", &w);
		pElement->Attribute("height", &h);
		rescfg.pos = Vec2((float)x, (float)y);
		rescfg.size = Vec2((float)w, (float)h);
		_cfg.sprite_cfg_list.push_back(rescfg);

		SpriteHandle = hSpritesRoot.Child ( "Sprite", ++index );
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
