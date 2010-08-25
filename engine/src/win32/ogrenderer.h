/*
 *  ogrenderer.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGRENDERER_H_
#define OGRENDERER_H_

#include "IOGRenderer.h"
#include "OpenGL2.h"
#include "ogmesh.h"
#include <list>


enum RenderCmdType
{
	RENDERCMD_NONE,
	RENDERCMD_SETTRANSFORM,
	RENDERCMD_SETMATERIAL,
	RENDERCMD_SETTEXTURE,
	RENDERCMD_SETMESH
};


struct RenderCommand
{
	RenderCommand () :	Type(RENDERCMD_NONE),
						pMaterial(NULL),
						pTexture(NULL),
						pPODMesh(NULL)
	{
	}

	RenderCmdType	Type;
	MATRIX			mWorld;
	IOGMaterial*	pMaterial;
	IOGTexture*		pTexture;
	SPODMesh*		pPODMesh;
	unsigned int	hVBO;
	unsigned int	hIBO;
};


class COGRenderer : public IOGRenderer
{
public:
	COGRenderer ();
	virtual ~COGRenderer ();
	
	// initialize renderer.
	virtual bool Init ();

	// add rendering command.
	virtual void SetTransform (const MATRIX& _mWorld);

	// add rendering command.
	virtual void SetTexture (IOGTexture* _pTexture);

	// add rendering command.
	virtual void SetMaterial (IOGMaterial* _pMaterial);

	// add rendering command.
	virtual void SetMesh (void* _pPODMesh,
		unsigned int _hVBO,
		unsigned int _hIBO);
	
	// render command buffer.
	virtual void Render (const MATRIX& _mView);
	
private:

	// Render command buffer
	std::list<RenderCommand>	m_CommandBuffer;
};

#endif
