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


class IOGRenderer
{
public:
	virtual ~IOGRenderer () {}
	
	// initialize renderer.
	virtual bool Init () = 0;

	// add rendering command.
	virtual void SetTexture (IOGTexture* _pTexture) = 0;

	// add rendering command.
	virtual void SetMaterial (IOGMaterial* _pMaterial) = 0;

	// add rendering command.
	virtual void RenderMesh (void* _pMesh) = 0;

	// start rendering meshes.
	virtual void StartRenderingMeshes() = 0;

	// finish rendering meshes.
	virtual void FinishRenderingMeshes() = 0;
	
	// reset renderer pipeline.
	virtual void Reset () = 0;
};

#endif
