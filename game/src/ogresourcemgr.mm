/*
 *  ogresourcemgr.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
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
}


COGResourceMgr::~COGResourceMgr ()
{
	std::map<std::string, COGTexture*>::iterator texture_iter = m_TextureList.begin();
	for( ; texture_iter != m_TextureList.end(); ++texture_iter )
	{
		delete texture_iter->second;
	}	

	std::map<std::string, COGMesh*>::iterator mesh_iter = m_MeshList.begin();
	for( ; mesh_iter != m_MeshList.end(); ++mesh_iter )
	{
		delete mesh_iter->second;
	}	
	
	std::map<std::string, COGModel*>::iterator model_iter = m_ModelList.begin();
	for( ; model_iter != m_ModelList.end(); ++model_iter )
	{
		delete model_iter->second;
	}
	
	std::map<std::string, COGTerrain*>::iterator terra_iter = m_TerrainList.begin();
	for( ; terra_iter != m_TerrainList.end(); ++terra_iter )
	{
		delete terra_iter->second;
	}
}


// load from file.
bool COGResourceMgr::Init (const char* _pResourceFile)
{
	char file_path[2048];
	GetResourcePathASCII(m_ResPath, 2048);

	COGTexture* pLoadScr = new COGTexture ();
	sprintf(file_path, "%s/load.pvr", m_ResPath);
	pLoadScr->LoadFromFile (file_path);
	m_TextureList["load_scr"] = pLoadScr;

	COGTexture* pLoadProgress = new COGTexture ();
	sprintf(file_path, "%s/load_progress.pvr", m_ResPath);
	pLoadProgress->LoadFromFile (file_path);
	m_TextureList["load_progress"] = pLoadProgress;
	
	m_pXmlSettings = new TiXmlDocument ( "resources.xml" );
	m_pXmlSettings->LoadFile (_pResourceFile);
	m_hDoc = new TiXmlHandle (m_pXmlSettings);
	
	m_NumTextures = GetNumElements ("Textures", "Texture");
	m_NumMeshes = GetNumElements ("Meshes", "Mesh");
	m_NumModels = GetNumElements ("Models", "Model");
	m_NumTerrains = GetNumElements ("Terrains", "Terrain");

	return true;
}


// get load progress.
float COGResourceMgr::GetLoadProgress ()
{
	if (!m_bTexturesLoaded)
	{
		float fPercent = (float)m_LoadIndex / (float)(m_NumTextures);
		return fPercent * 40.0f;
	}
	if (!m_bMeshesLoaded)
	{
		float fPercent = (float)m_LoadIndex / (float)(m_NumMeshes);
		return fPercent * 40.0f + 40.0f;
	}
	if (!m_bModelsLoaded)
	{
		float fPercent = (float)m_LoadIndex / (float)(m_NumModels);
		return fPercent * 10.0f + 80.0f;
	}
	if (!m_bTerrainsLoaded)
	{
		float fPercent = (float)m_LoadIndex / (float)(m_NumTerrains);
		return fPercent * 10.0f + 90.0f;
	}
	return 100.0f;
}


// load resource.
bool COGResourceMgr::LoadNext ()
{
	if (!m_bTexturesLoaded)
	{
		if (LoadNextTexture(m_LoadIndex))
		{
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
		COGTexture* pTexture = new COGTexture ();
		sprintf(file_path, "%s/%s", m_ResPath, texture_file);
		pTexture->LoadFromFile (file_path);
		m_TextureList[texture_alias] = pTexture;
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
		COGMesh* pMesh = new COGMesh ();
		sprintf(file_path, "%s/%s", m_ResPath, mesh_file);
		pMesh->Load (file_path);
		m_MeshList[mesh_alias] = pMesh;
		return true;
	}
	return false;
}


// load next model resource.
bool COGResourceMgr::LoadNextModel (int _Iteration)
{
	TiXmlHandle hModelsRoot = m_hDoc->FirstChild ( "Models" );
	TiXmlHandle ModelHandle = hModelsRoot.Child ( "Model", _Iteration );
	if (ModelHandle.Node ())
	{
		TiXmlElement* pElement = ModelHandle.Element();
		const char* model_alias = pElement->Attribute ("alias");
		const char* model_mesh_alias = pElement->Attribute ("mesh");
		const char* model_texture_alias = pElement->Attribute ("texture");
		COGModel* pModel = new COGModel ();
		pModel->Load (GetMesh(model_mesh_alias), GetTexture(model_texture_alias));
		m_ModelList[model_alias] = pModel;
		return true;
	}
	return false;
}


// load next terrain.
bool COGResourceMgr::LoadNextTerrain (int _Iteration)
{
	char file_path[2048];
	TiXmlHandle hTerrainsRoot = m_hDoc->FirstChild ( "Terrains" );
	TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Terrain", _Iteration );
	if (TerrainHandle.Node ())
	{
		TiXmlElement* pElement = TerrainHandle.Element();
		const char* terrain_alias = pElement->Attribute ("alias");
		const char* terrain_file = pElement->Attribute ("file");
		COGTerrain* pTerrain = new COGTerrain ();
		sprintf(file_path, "%s/%s", m_ResPath, terrain_file);
		pTerrain->Load (file_path, 128, 128);
		pTerrain->SetTextureLayer(GetTexture("land_grass"));
		m_TerrainList[terrain_alias] = pTerrain;
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
	return m_TerrainList[_pAlias];
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