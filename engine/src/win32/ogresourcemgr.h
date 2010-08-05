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
	virtual bool Init ();

    // get resource path
    virtual const std::string& GetResourcePath () const;

	// load resources.
	virtual bool Load (std::vector<IOGResourceInfo>& _resInfo);

	// get texture.
	virtual IOGTexture* GetTexture (const std::string& _pAlias);
	
	// get mesh.
	virtual IOGMesh* GetMesh (const std::string& _pAlias);
	
	// get model.
	virtual IOGModel* GetModel (const std::string& _pAlias);

	// get terrain.
	virtual IOGTerrain* GetTerrain (const std::string& _pAlias);

	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture);
		
	// release mesh.
	virtual void ReleaseMesh (IOGMesh* _pMesh);
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel);
		
	// release terrain.
	virtual void ReleaseTerrain (IOGTerrain* _pTerrain);
	
private:

	struct Cfg
	{
		struct ResourceCfg
		{
			std::string alias;
			std::string file;
			std::string icon;
		};

		std::vector<ResourceCfg> texture_cfg_list;
		std::vector<ResourceCfg> mesh_cfg_list;
		std::vector<ResourceCfg> model_cfg_list;
		std::vector<ResourceCfg> terrain_cfg_list;
	};

	// Load resource manager configuration
	bool LoadConfig (COGResourceMgr::Cfg& _cfg);
	
private:

	std::map<std::string, COGTexture*>	m_TextureList;
	std::map<std::string, COGMesh*>		m_MeshList;
	std::map<std::string, COGModel*>	m_ModelList;
	std::map<std::string, COGTerrain*>	m_TerrainList;
	std::string							m_ResPath;
};

#endif