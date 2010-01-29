/*
 *  IOGTerrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef IOGTERRAIN_H_
#define IOGTERRAIN_H_

#include "Mathematics.h"
#include "IOGTexture.h"


class IOGTerrain
{
public:
	virtual ~IOGTerrain() {}
	
	// Load terrain.
	virtual bool Load (const char* _pTerrainFile, int _Width, int _Height) = 0;
	
	// Set terrain texture layer.
	virtual void SetTextureLayer (IOGTexture* _pTexture) = 0;
	
	// Render terrain.
	virtual void Render (const MATRIX& _mView) = 0;
};


#endif