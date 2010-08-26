/*
 *  IOGMaterialManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMATERIALMANAGER_H_
#define IOGMATERIALMANAGER_H_

#include "IOGMaterial.h"
#include <string>


class IOGMaterialManager
{
public:
	virtual ~IOGMaterialManager () {}
		
	// initialize materials.
	virtual bool Init () = 0;

	// get material.
	virtual IOGMaterial* GetMaterial (const std::string& _Alias) = 0;

	// get material.
	virtual IOGMaterial* GetMaterial (OGMaterialType _Type) = 0;
};

#endif
