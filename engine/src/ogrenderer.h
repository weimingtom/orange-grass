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
#include "IOGStatistics.h"
#include "ogmesh.h"
#include "ogrendertarget.h"
#include "ogtextrenderer.h"
#include <string>
#include <map>


class COGRenderer : public IOGRenderer
{
public:
	COGRenderer ();
	virtual ~COGRenderer ();

	// initialize renderer.
	virtual bool Init ();
	
	// set viewport.
	virtual void SetViewport (
		unsigned int _Width, 
		unsigned int _Height,
		float _fZNear,
		float _fZFar,
		float _fFOV);

	// add rendering command.
	virtual void SetTexture (IOGTexture* _pTexture);

	// add rendering command.
	virtual void SetMaterial (IOGMaterial* _pMaterial);

	// add rendering command.
	virtual void SetBlend (OGBlendType _Blend);

	// add rendering command.
	virtual void RenderMesh (void* _pMesh);

	// clear frame buffer with the given color
	virtual void ClearFrame (const Vec4& _vClearColor);

	// Create material.
	virtual IOGMaterial* CreateMaterial ();

	// Get scene light.
	virtual IOGLightMgr* GetLightMgr ();

	// Get main camera.
	virtual IOGCamera* GetCamera ();

	// Get fog.
	virtual IOGFog* GetFog ();

	// reset renderer pipeline.
	virtual void Reset ();

    // Unproject screen coords.
    virtual Vec3 UnprojectCoords (int _X, int _Y);

    // Display string.
    virtual void DisplayString (
		const Vec2& _vPos, 
		float _fScale, 
		unsigned int Colour, 
		const char * const pszFormat, ...);

    // Draw shadow texture.
    virtual void DrawShadowTexture () {}

protected:

    IOGTexture*         m_pCurTexture;
    IOGMaterial*        m_pCurMaterial;
    IOGVertexBuffers*	m_pCurMesh;
	OGBlendType			m_CurBlend;
	IOGStatistics*		m_pStats;
	IOGFog*				m_pFog;
	IOGLightMgr*		m_pLightMgr;
	IOGCamera*			m_pCamera;
	COGTextRenderer*	m_pText;
	MATRIX				m_mOrthoProj;
	MATRIX				m_mProjection;
    MATRIX              m_mTextProj;
	MATRIX				m_mView;
	unsigned int		m_Width; 
	unsigned int		m_Height;
	float				m_fZNear;
	float				m_fZFar;
	float				m_fFOV;
	bool				m_bLandscapeMode;
	OGRenderMode		m_Mode;
};

#endif
