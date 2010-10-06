/*
 *  ogrenderer_gles20.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGRENDERER_GLES20_H_
#define OGRENDERER_GLES20_H_

#include "ogrenderer.h"
#include "ogmodelshader.h"
#include "ogspriteshader.h"
#include "ogcoloreffectshader.h"
#include "ogtextshader.h"


class COGRenderer_GLES20 : public COGRenderer
{
public:
	COGRenderer_GLES20 ();
	virtual ~COGRenderer_GLES20 ();

	// initialize renderer.
	virtual bool Init ();

	// Create vertex buffer for mesh.
	virtual IOGVertexBuffers* CreateVertexBuffer (const void* _pMeshData);

	// set model matrix.
	virtual void SetModelMatrix (const MATRIX& _mModel);

	// set view matrix.
	virtual void SetViewMatrix (const MATRIX& _mView);

	// Enable scene light.
	virtual void EnableLight (bool _bEnable);

	// Enable scene fog.
	virtual void EnableFog (bool _bEnable);

	// start rendering mode.
	virtual void StartRenderMode(OGRenderMode _Mode);

	// finish rendering mode.
	virtual void FinishRenderMode();

	// add rendering command.
	virtual void RenderMesh (void* _pMesh);

    // Draw effects buffer.
    virtual void DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices);

    // Draw sprite buffer.
    virtual void DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices);

protected:

	MATRIX	m_mWorld;
    bool    m_bLightEnabled;
    bool    m_bFogEnabled;

    COGModelShader          m_ModelShader;
    COGSpriteShader         m_SpriteShader;
    COGColorEffectShader    m_ColorEffectShader;
    COGTextShader           m_TextShader;
    IOGShader*              m_pCurShader;
};

#endif
