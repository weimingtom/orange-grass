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


class COGRenderer : public IOGRenderer
{
public:
	COGRenderer ();
	virtual ~COGRenderer ();
	
	// initialize renderer.
	virtual bool Init ();

	// add rendering command.
	virtual void SetTexture (IOGTexture* _pTexture);

	// add rendering command.
	virtual void SetMaterial (IOGMaterial* _pMaterial);

	// add rendering command.
	virtual void RenderMesh (void* _pMesh);

	// start rendering meshes.
	virtual void StartRenderingMeshes();

	// finish rendering meshes.
	virtual void FinishRenderingMeshes();

	// reset renderer pipeline.
	virtual void Reset ();
	
private:

    IOGTexture*         m_pCurTexture;
    IOGMaterial*        m_pCurMaterial;
    COGVertexBuffers*	m_pCurMesh;
};

#endif
