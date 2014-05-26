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
#ifndef IOGRESOURCEMGR_H_
#define IOGRESOURCEMGR_H_

#include "IOGTexture.h"
#include "IOGModel.h"
#include "IOGSprite.h"
#include <string>


enum OGResourcePool
{
	OG_RESPOOL_NONE,
	OG_RESPOOL_UI,
	OG_RESPOOL_GAME
};


// Resource loading state
enum OGResourceState
{
    OG_RESSTATE_UNKNOWN,
    OG_RESSTATE_DEFINED,
    OG_RESSTATE_LOADED,
};


class IOGResourceMgr
{
public:
	virtual ~IOGResourceMgr () {}

    // get full resource path
    virtual std::string GetFullPath (const std::string& _File) const = 0;

    // get UI resource path
    virtual std::string GetUIPath (const std::string& _File) const = 0;

	// load resources.
	virtual bool Load (OGResourcePool _PoolId) = 0;

	// unload resources.
	virtual bool Unload (OGResourcePool _PoolId) = 0;

	// get texture.
	virtual IOGTexture* GetTexture (OGResourcePool _PoolId, const std::string& _Alias) = 0;

	// get model.
	virtual IOGModel* GetModel (OGResourcePool _PoolId, const std::string& _Alias) = 0;

	// get sprite.
	virtual IOGSprite* GetSprite (OGResourcePool _PoolId, const std::string& _Alias) = 0;
	
	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture) = 0;
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel) = 0;

	// release sprite.
	virtual void ReleaseSprite (IOGSprite* _pSprite) = 0;
};

#endif
