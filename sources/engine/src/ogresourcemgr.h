/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGRESOURCEMGR_H_
#define OGRESOURCEMGR_H_

#include "IOGResourceMgr.h"
#include "ogtexture.h"
#include "ogmesh.h"
#include "ogmodel.h"
#include "ogsprite.h"
#include <string>
#include <map>
#include <list>
#include "IOGSettingsReader.h"


class COGResourceMgr : public IOGResourceMgr
{
public:
	COGResourceMgr ();
	virtual ~COGResourceMgr ();

    // get full resource path
    virtual std::string GetFullPath (const std::string& _File) const;

    // get UI resource path
    virtual std::string GetUIPath (const std::string& _File) const;

	// load resources.
	virtual bool Load (OGResourcePool _PoolId);

	// unload resources.
	virtual bool Unload (OGResourcePool _PoolId);

	// get texture.
	virtual IOGTexture* GetTexture (OGResourcePool _PoolId, const std::string& _Alias);
	
	// get model.
	virtual IOGModel* GetModel (OGResourcePool _PoolId, const std::string& _Alias);

	// get sprite.
	virtual IOGSprite* GetSprite (OGResourcePool _PoolId, const std::string& _Alias);

	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture);
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel);

	// release sprite.
	virtual void ReleaseSprite (IOGSprite* _pSprite);
	
private:

	struct Cfg
	{
		struct TextureResourceCfg
		{
			struct MappingCfg
			{
				OGVec2 pos;
				OGVec2 size;
			};

			std::string alias;
			std::string file;
			std::list<MappingCfg> mappings;
		};

		struct ModelResourceCfg
		{
			std::string alias;
			std::string file;
		};

		struct SpriteResourceCfg
		{
			std::string alias;
			std::string texture;
			unsigned int mapping;
		};

		typedef std::list<TextureResourceCfg>	TTextureCfg;
		typedef std::list<ModelResourceCfg>		TModelCfg;
		typedef std::list<SpriteResourceCfg>	TSpriteCfg;

		TTextureCfg	texture_cfg_list;
		TModelCfg	model_cfg_list;
		TSpriteCfg	sprite_cfg_list;
	};

	struct ResourcePool
	{
		ResourcePool() : m_bLoaded(false) {}
		std::map<std::string, COGTexture*>	m_TextureList;
		std::map<std::string, COGModel*>	m_ModelList;
		std::map<std::string, COGSprite*>	m_SpriteList;
		bool								m_bLoaded;
	};

	// Load resource manager configuration
	bool LoadConfig (COGResourceMgr::Cfg& _cfg, const std::string& _ConfigFile);

	// clear resource pool.
	bool ClearPool (OGResourcePool _PoolId);
	
private:

	ResourcePool		m_PoolUI;
	ResourcePool		m_PoolGame;
	IOGSettingsReader*	m_pReader;
};

#endif
