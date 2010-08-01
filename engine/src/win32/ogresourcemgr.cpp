/*
 *  ogresourcemgr.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "ogresourcemgr.h"
#include "Pathes.h"


COGResourceMgr::COGResourceMgr () :	m_bTexturesLoaded(false),
									m_bMeshesLoaded(false),
									m_bModelsLoaded(false),
									m_bTerrainsLoaded(false),
									m_LoadIndex(0),
									m_NumTextures(0),
									m_NumMeshes(0),
									m_NumModels(0),
									m_NumTerrains(0)
{
	GetResourcePathASCII(m_ResPath, 2048);
	sprintf(m_ResPath, "%sGameResources", m_ResPath);
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
bool COGResourceMgr::Init (const char* _pResourceFile)
{
	char file_path[2048];

	COGTexture* pLoadScr = new COGTexture ();
	sprintf(file_path, "%s\\GUI\\load.pvr", m_ResPath);
	pLoadScr->Init ("load_scr", file_path);
	pLoadScr->Load ();
	m_TextureList["load_scr"] = pLoadScr;

	COGTexture* pLoadProgress = new COGTexture ();
	sprintf(file_path, "%s\\GUI\\load_progress.pvr", m_ResPath);
	pLoadProgress->Init ("load_progress", file_path);
	pLoadProgress->Load ();
	m_TextureList["load_progress"] = pLoadProgress;
	
	m_pXmlSettings = new TiXmlDocument ( "resources.xml" );
	sprintf(file_path, "%s\\%s", m_ResPath, _pResourceFile);
	if (!m_pXmlSettings->LoadFile (file_path))
		return false;
	m_hDoc = new TiXmlHandle (m_pXmlSettings);
	
	m_NumTextures = GetNumElements ("Textures", "Texture");
	m_NumMeshes = GetNumElements ("Meshes", "Mesh");
	m_NumModels = GetNumElements ("Models", "Model");
	m_NumTerrains = GetNumElements ("Terrains", "Terrain");

	return true;
}


// get resource path
const char* COGResourceMgr::GetResourcePath () const
{
    return m_ResPath;
}


// load resource.
bool COGResourceMgr::LoadNext (IOGResourceInfo& _resInfo)
{
	if (!m_bTexturesLoaded)
	{
		if (LoadNextTexture(m_LoadIndex))
		{
        	_resInfo = m_LoadedResourceInfo;
			++m_LoadIndex;
			return true;
		}
		else
		{
			m_bTexturesLoaded = true;
			m_LoadIndex = 0;
		}
	}
	if (!m_bMeshesLoaded)
	{
		if (LoadNextMesh(m_LoadIndex))
		{
        	_resInfo = m_LoadedResourceInfo;
			++m_LoadIndex;
			return true;
		}
		else
		{
			m_bMeshesLoaded = true;
			m_LoadIndex = 0;
		}
	}
	if (!m_bModelsLoaded)
	{
		if (LoadNextModel(m_LoadIndex))
		{
        	_resInfo = m_LoadedResourceInfo;
			++m_LoadIndex;
			return true;
		}
		else
		{
			m_bModelsLoaded = true;
			m_LoadIndex = 0;
		}
	}
	if (!m_bTerrainsLoaded)
	{
		if (LoadNextTerrain(m_LoadIndex))
		{
        	_resInfo = m_LoadedResourceInfo;
			++m_LoadIndex;
			return true;
		}
		else
		{
			m_bTerrainsLoaded = true;
			m_LoadIndex = 0;
		}
	}
	
	if (m_bTexturesLoaded && m_bMeshesLoaded && m_bModelsLoaded && m_bTerrainsLoaded)
	{
		m_LoadIndex = 0;
		delete m_hDoc;
		m_hDoc = NULL;
		delete m_pXmlSettings;
		m_pXmlSettings = NULL;
	}
	return false;
}


// load next texture resource.
bool COGResourceMgr::LoadNextTexture (int _Iteration)
{
	char file_path[2048];
	TiXmlHandle hTexturesRoot = m_hDoc->FirstChild ( "Textures" );
	TiXmlHandle TextureHandle = hTexturesRoot.Child ( "Texture", _Iteration );
	if (TextureHandle.Node ())
	{
		TiXmlElement* pElement = TextureHandle.Element();
		const char* texture_alias = pElement->Attribute ("alias");
		const char* texture_file = pElement->Attribute ("file");
		sprintf(file_path, "%s/%s", m_ResPath, texture_file);
		COGTexture* pTexture = new COGTexture ();
		pTexture->Init (texture_alias, file_path);
		pTexture->Load ();
		m_TextureList[texture_alias] = pTexture;
		sprintf(m_LoadedResourceInfo.m_pResource, texture_alias);
		sprintf(m_LoadedResourceInfo.m_pResourceGroup, "Textures");
		sprintf(m_LoadedResourceInfo.m_pResourceIcon, "");
		return true;
	}
	return false;
}


// load next mesh resource.
bool COGResourceMgr::LoadNextMesh (int _Iteration)
{
	char file_path[2048];
	TiXmlHandle hMeshesRoot = m_hDoc->FirstChild ( "Meshes" );
	TiXmlHandle MeshHandle = hMeshesRoot.Child ( "Mesh", _Iteration );
	if (MeshHandle.Node ())
	{
		TiXmlElement* pElement = MeshHandle.Element();
		const char* mesh_alias = pElement->Attribute ("alias");
		const char* mesh_file = pElement->Attribute ("file");
		sprintf(file_path, "%s/%s", m_ResPath, mesh_file);
		COGMesh* pMesh = new COGMesh ();
		pMesh->Init (mesh_alias, file_path);
		pMesh->Load ();
		m_MeshList[mesh_alias] = pMesh;
		sprintf(m_LoadedResourceInfo.m_pResource, mesh_alias);
		sprintf(m_LoadedResourceInfo.m_pResourceGroup, "Meshes");
		sprintf(m_LoadedResourceInfo.m_pResourceIcon, "");
		return true;
	}
	return false;
}


// load next model resource.
bool COGResourceMgr::LoadNextModel (int _Iteration)
{
	char file_path[256];
	TiXmlHandle hModelsRoot = m_hDoc->FirstChild ( "Models" );
	TiXmlHandle ModelHandle = hModelsRoot.Child ( "Model", _Iteration );
	if (ModelHandle.Node ())
	{
		TiXmlElement* pElement = ModelHandle.Element();
		const char* model_alias = pElement->Attribute ("alias");
		const char* model_file = pElement->Attribute ("file");
		sprintf(file_path, "%s\\%s", m_ResPath, model_file);
		COGModel* pModel = new COGModel ();
		pModel->Init (model_alias, file_path);
		pModel->Load ();
		m_ModelList[model_alias] = pModel;
		sprintf(m_LoadedResourceInfo.m_pResource, model_alias);
		sprintf(m_LoadedResourceInfo.m_pResourceGroup, "Models");
		sprintf(m_LoadedResourceInfo.m_pResourceIcon, "%s\\%s", m_ResPath, pModel->GetResourceIcon());
		return true;
	}
	return false;
}


// load next terrain resource.
bool COGResourceMgr::LoadNextTerrain (int _Iteration)
{
	char file_path[256];
	TiXmlHandle hTerrainsRoot = m_hDoc->FirstChild ( "Terrains" );
	TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Terrain", _Iteration );
	if (TerrainHandle.Node ())
	{
		TiXmlElement* pElement = TerrainHandle.Element();
		const char* terrain_alias = pElement->Attribute ("alias");
		const char* terrain_file = pElement->Attribute ("file");
		sprintf(file_path, "%s\\%s", m_ResPath, terrain_file);
		COGTerrain* pTerrain = new COGTerrain ();
		pTerrain->Init (terrain_alias, file_path);
		m_TerrainList[terrain_alias] = pTerrain;
		sprintf(m_LoadedResourceInfo.m_pResource, terrain_alias);
		sprintf(m_LoadedResourceInfo.m_pResourceGroup, "Terrains");
        sprintf(m_LoadedResourceInfo.m_pResourceIcon, "%s\\%s", m_ResPath, pTerrain->GetResourceIcon());
		return true;
	}
	return false;
}


// get texture
IOGTexture* COGResourceMgr::GetTexture (const char* _pAlias)
{
	return m_TextureList[_pAlias];
}


// get mesh
IOGMesh* COGResourceMgr::GetMesh (const char* _pAlias)
{
	return m_MeshList[_pAlias];
}


// get model
IOGModel* COGResourceMgr::GetModel (const char* _pAlias)
{
	return m_ModelList[_pAlias];
}


// get terrain.
IOGTerrain* COGResourceMgr::GetTerrain (const char* _pAlias)
{
	COGTerrain* pTerrain = m_TerrainList[_pAlias];
    if (pTerrain)
    {
        pTerrain->SetWorldPosition (Vec3(0, 0, 0));
        if (pTerrain->Load() == NULL)
            return NULL;
        return pTerrain;
    }
    return NULL;
}


// get number of elements
int COGResourceMgr::GetNumElements (const char* _pNodeName, const char* _pElementName)
{
	int Index = 0;
	TiXmlHandle hEntryRoot = m_hDoc->FirstChild (_pNodeName);
	TiXmlHandle entryHandle = hEntryRoot.Child ( _pElementName, Index );
	while (entryHandle.Node ())
	{
		++Index;
		entryHandle = hEntryRoot.Child ( _pElementName, Index );
	}
	return Index;
}
