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
#include "ogsprite.h"
#include "tinyxml.h"
#include <string>
#include <map>
#include <list>


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
	virtual bool Load ();

	// get texture.
	virtual IOGTexture* GetTexture (const std::string& _Alias);
	
	// get mesh.
	virtual IOGMesh* GetMesh (const std::string& _Alias);
	
	// get model.
	virtual IOGModel* GetModel (const std::string& _Alias);

	// get terrain.
	virtual IOGTerrain* GetTerrain (const std::string& _Alias);

	// get sprite.
	virtual IOGSprite* GetSprite (const std::string& _Alias);

	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture);
		
	// release mesh.
	virtual void ReleaseMesh (IOGMesh* _pMesh);
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel);

	// release terrain.
	virtual void ReleaseTerrain (IOGTerrain* _pTerrain);

	// release sprite.
	virtual void ReleaseSprite (IOGSprite* _pSprite);
	
private:

	struct Cfg
	{
		struct TextureResourceCfg
		{
			struct MappingCfg
			{
				Vec2 pos;
				Vec2 size;
			};

			std::string alias;
			std::string file;
			std::list<MappingCfg> mappings;
		};

		struct MeshResourceCfg
		{
			std::string alias;
			std::string file;
		};

		struct ModelResourceCfg
		{
			std::string alias;
			std::string file;
		};

		struct TerrainResourceCfg
		{
			std::string alias;
			std::string file;
		};

		struct SpriteResourceCfg
		{
			std::string alias;
			std::string texture;
			Vec2		pos;
			Vec2		size;
		};

		typedef std::list<TextureResourceCfg>	TTextureCfg;
		typedef std::list<MeshResourceCfg>		TMeshCfg;
		typedef std::list<ModelResourceCfg>		TModelCfg;
		typedef std::list<TerrainResourceCfg>	TTerrainCfg;
		typedef std::list<SpriteResourceCfg>	TSpriteCfg;

		TTextureCfg	texture_cfg_list;
		TMeshCfg	mesh_cfg_list;
		TModelCfg	model_cfg_list;
		TTerrainCfg	terrain_cfg_list;
		TSpriteCfg	sprite_cfg_list;
	};

	// Load resource manager configuration
	bool LoadConfig (COGResourceMgr::Cfg& _cfg);
	
private:

	std::map<std::string, COGTexture*>	m_TextureList;
	std::map<std::string, COGMesh*>		m_MeshList;
	std::map<std::string, COGModel*>	m_ModelList;
	std::map<std::string, COGTerrain*>	m_TerrainList;
	std::map<std::string, COGSprite*>	m_SpriteList;
	std::string							m_ResPath;
};

#endif