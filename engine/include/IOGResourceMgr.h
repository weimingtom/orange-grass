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


class IOGResourceMgr
{
public:
	virtual ~IOGResourceMgr () {}
		
	// load from file.
	virtual bool Init () = 0;

    // get resource path
    virtual const std::string& GetResourcePath () const = 0;

    // get full resource path
    virtual std::string GetFullPath (const std::string& _File) const = 0;

	// load resources.
	virtual bool Load () = 0;
		
	// get texture.
	virtual IOGTexture* GetTexture (const std::string& _Alias) = 0;

	// get model.
	virtual IOGModel* GetModel (const std::string& _Alias) = 0;

	// get sprite.
	virtual IOGSprite* GetSprite (const std::string& _Alias) = 0;
	
	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture) = 0;
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel) = 0;

	// release sprite.
	virtual void ReleaseSprite (IOGSprite* _pSprite) = 0;
};

#endif
