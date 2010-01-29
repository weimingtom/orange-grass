/*
 *  IOGModel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMODEL_H_
#define IOGMODEL_H_

#include "IOGTexture.h"
#include "IOGMesh.h"


class IOGModel
{
public:
	virtual ~IOGModel() {}
		
	// Load model.
	virtual bool Load (IOGMesh* _pMesh, IOGTexture* _pTexture) = 0;
		
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) = 0;
		
	// Render mesh.
	virtual void Render (const MATRIX& _mView) = 0;
};


#endif
