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
#include "IOGMesh.h"
#include "IOGModel.h"
#include "IOGTerrain.h"
#include <string>


struct IOGResourceInfo
{
	std::string m_Resource;
	std::string m_ResourceIcon;
	std::string m_ResourceGroup;
};


class IOGResourceMgr
{
public:
	virtual ~IOGResourceMgr () {}
		
	// load from file.
	virtual bool Init () = 0;

    // get resource path
    virtual const std::string& GetResourcePath () const = 0;

	// load resources.
	virtual bool Load (std::vector<IOGResourceInfo>& _resInfo) = 0;
		
	// get texture.
	virtual IOGTexture* GetTexture (const std::string& _Alias) = 0;
		
	// get mesh.
	virtual IOGMesh* GetMesh (const std::string& _Alias) = 0;

	// get model.
	virtual IOGModel* GetModel (const std::string& _Alias) = 0;

	// get terrain.
	virtual IOGTerrain* GetTerrain (const std::string& _Alias) = 0;
		
	// release texture.
	virtual void ReleaseTexture (IOGTexture* _pTexture) = 0;
		
	// release mesh.
	virtual void ReleaseMesh (IOGMesh* _pMesh) = 0;
		
	// release model.
	virtual void ReleaseModel (IOGModel* _pModel) = 0;
		
	// release terrain.
	virtual void ReleaseTerrain (IOGTerrain* _pTerrain) = 0;
};

#endif
