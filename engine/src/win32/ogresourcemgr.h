/*
 *  ogresourcemgr.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGRESOURCEMGR_H_
#define OGRESOURCEMGR_H_

#include "OpenGL2.h"
#include "IOGResourceMgr.h"
#include "common.h"
#include "ogtexture.h"
#include "ogmesh.h"
#include "ogmodel.h"
#include "ogterrain.h"
#include "tinyxml.h"
#include <string>
#include <map>


class COGResourceMgr : public IOGResourceMgr
{
public:
	COGResourceMgr ();
	virtual ~COGResourceMgr ();
	
	// load from file.
	virtual bool Init (const char* _pResourceFile);

    // get resource path
    virtual const char* GetResourcePath () const;

	// load next resource.
	virtual bool LoadNext (IOGResourceInfo& _resInfo);

	// get texture.
	virtual IOGTexture* GetTexture (const char* _pAlias);
	
	// get mesh.
	virtual IOGMesh* GetMesh (const char* _pAlias);
	
	// get model.
	virtual IOGModel* GetModel (const char* _pAlias);

	// get terrain.
	virtual IOGTerrain* GetTerrain (const char* _pAlias);
	
private:
		
	// load next texture resource.
	bool LoadNextTexture (int _Iteration);
	
	// load next mesh resource.
	bool LoadNextMesh (int _Iteration);

	// load next model resource.
	bool LoadNextModel (int _Iteration);

	// load next terrain resource.
	bool LoadNextTerrain (int _Iteration);
	
	// get number of elements
	int GetNumElements (const char* _pNodeName, const char* _pElementName);
	
private:

	std::map<std::string, COGTexture*>	m_TextureList;
	std::map<std::string, COGMesh*>		m_MeshList;
	std::map<std::string, COGModel*>	m_ModelList;
	std::map<std::string, COGTerrain*>	m_TerrainList;
	char								m_ResPath[2048];
	bool								m_bTexturesLoaded;
	bool								m_bMeshesLoaded;
	bool								m_bModelsLoaded;
	bool								m_bTerrainsLoaded;
	int									m_LoadIndex;
	TiXmlHandle*						m_hDoc;
	TiXmlDocument*						m_pXmlSettings;
	int									m_NumTextures;
	int									m_NumMeshes;
	int									m_NumModels;
	int									m_NumTerrains;
	IOGResourceInfo						m_LoadedResourceInfo;
};

#endif