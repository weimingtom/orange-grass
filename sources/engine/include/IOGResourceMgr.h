/*
 *  IOGResourceMgr.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
