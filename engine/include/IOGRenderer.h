/*
 *  IOGRenderer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGRENDERER_H_
#define IOGRENDERER_H_

#include "IOGTexture.h"
#include "IOGMaterial.h"
#include "IOGMesh.h"


class IOGRenderer
{
public:
	virtual ~IOGRenderer () {}
	
	// initialize renderer.
	virtual bool Init () = 0;

	// add rendering command.
	virtual void SetTransform (const MATRIX& _mWorld) = 0;

	// add rendering command.
	virtual void SetTexture (IOGTexture* _pTexture) = 0;

	// add rendering command.
	virtual void SetMaterial (IOGMaterial* _pMaterial) = 0;

	// add rendering command.
	virtual void SetMesh (void* _pPODMesh,
		unsigned int _hVBO,
		unsigned int _hIBO) = 0;
	
	// render command buffer.
	virtual void Render (const MATRIX& _mView) = 0;
};

#endif
