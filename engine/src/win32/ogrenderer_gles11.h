/*
 *  ogrenderer_gles11.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGRENDERER_GLES11_H_
#define OGRENDERER_GLES11_H_

#include "ogrenderer.h"


class COGRenderer_GLES11 : public COGRenderer
{
public:
	COGRenderer_GLES11 ();
	virtual ~COGRenderer_GLES11 ();

	// initialize renderer.
	virtual bool Init ();

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

    // Draw effects buffer.
    virtual void DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices);

    // Draw sprite buffer.
    virtual void DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices);

protected:

	MATRIX	m_mModelView;
};

#endif
