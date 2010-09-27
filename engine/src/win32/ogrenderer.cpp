/*
 *  ogrenderer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogrenderer.h"
#include "oglight.h"
#include "ogcamera.h"
#include "ogfog.h"
#include "ogsprite.h"


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL),
								m_pFog(NULL),
								m_pLight(NULL),
								m_pCamera(NULL)
{
	m_pStats = GetStatistics();
}


COGRenderer::~COGRenderer ()
{
	OG_SAFE_DELETE(m_pFog);
	OG_SAFE_DELETE(m_pLight);
	OG_SAFE_DELETE(m_pCamera);
}


// initialize renderer.
bool COGRenderer::Init ()
{
    glClearColor(0.3f, 0.3f, 0.4f, 1.0f);

    glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Reset();
	m_pLight = new COGLight ();
	m_pCamera = new COGCamera ();
	m_pFog = new COGFog ();
	return true;
}

	
// set viewport.
void COGRenderer::SetViewport (
							   unsigned int _Width, 
							   unsigned int _Height,
							   float _fZNear,
							   float _fZFar,
							   float _fFOV )
{
	m_Width = _Width;
	m_Height = _Height;
	m_fFOV = _fFOV;
	m_fZNear = _fZNear;
	m_fZFar = _fZFar;

#ifdef WIN32
	MatrixOrthoRH(m_mOrthoProj, (float)m_Width, (float)m_Height, -1, 1, false);
    MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Width)/float(m_Height), m_fZNear, m_fZFar, false);
#else
	MatrixOrthoRH(m_mOrthoProj, (float)m_Height, (float)m_Width, -1, 1, true);
    MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Height)/float(m_Width), m_fZNear, m_fZFar, true);
#endif
}


// add rendering command.
void COGRenderer::SetTexture (IOGTexture* _pTexture)
{
    if (_pTexture != m_pCurTexture)
    {
		m_pStats->AddTextureSwitch();
        m_pCurTexture = _pTexture;
        m_pCurTexture->Apply();
    }
}


// add rendering command.
void COGRenderer::SetMaterial (IOGMaterial* _pMaterial)
{
	if (m_Mode == OG_RENDERMODE_SHADOWMAP)
		return;

    if (_pMaterial != m_pCurMaterial)
    {
        m_pCurMaterial = _pMaterial;
        m_pCurMaterial->Apply();
    }
}


// add rendering command.
void COGRenderer::RenderMesh (void* _pMesh)
{
	if ((COGVertexBuffers*)_pMesh != m_pCurMesh)
    {
        m_pCurMesh = (COGVertexBuffers*)_pMesh;
        m_pCurMesh->Apply();
    }
    m_pCurMesh->Render();
}


// clear frame buffer with the given color
void COGRenderer::ClearFrame (const Vec4& _vClearColor)
{
	glClearColor(_vClearColor.x, _vClearColor.y, _vClearColor.z, _vClearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


// Get scene light.
IOGLight* COGRenderer::GetLight ()
{
	return m_pLight;
}


// Get main camera.
IOGCamera* COGRenderer::GetCamera ()
{
	return m_pCamera;
}


// Get fog.
IOGFog* COGRenderer::GetFog ()
{
	return m_pFog;
}


// start rendering mode.
void COGRenderer::StartRenderMode(OGRenderMode _Mode)
{
	m_Mode = _Mode;
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
	    glEnable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);
	    glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mProjection.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m_pCamera->GetViewMatrix().f);
		m_pLight->Enable(true);
		m_pLight->Apply();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		break;
		
	case OG_RENDERMODE_EFFECTS:
	    glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mProjection.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m_pCamera->GetViewMatrix().f);
		m_pLight->Enable(false);
		glDisable(GL_CULL_FACE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);	
		break;
	
	case OG_RENDERMODE_SPRITES:
		m_pLight->Enable(false);
		glDisable(GL_DEPTH_TEST);
	    glDisable(GL_CULL_FACE);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mOrthoProj.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;
	}
}


// finish rendering mode.
void COGRenderer::FinishRenderMode()
{
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
#ifdef USE_VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		break;
	
	case OG_RENDERMODE_EFFECTS:
		glDisable(GL_BLEND); 
	    glEnable(GL_CULL_FACE);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
		glDisableClientState(GL_COLOR_ARRAY);
		break;
	
	case OG_RENDERMODE_SPRITES:
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;
	}
}


// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
}


// Unproject screen coords.
Vec3 COGRenderer::UnprojectCoords (int _X, int _Y)
{
	// Get the inverse of the view matrix
	MATRIX mInv, mMul;
    MATRIX mView = m_pCamera->GetViewMatrix();
	MatrixMultiply (mMul, m_mProjection, m_pCamera->GetViewMatrix());
	//MatrixMultiply (mMul, mView, m_mProjection);
	MatrixInverse (mInv, mMul);

	//// Compute the vector of the pick ray in screen space
 //   Vec4 v;
	//v.x = ( ( ( 2.0f * _X ) / 480 ) - 1.0f );
	//v.y = ( ( ( 2.0f * _Y ) / 320 ) - 1.0f );
	//v.z = 2.0f * 0.0f - 1.0f;
	//v.w = 1.0f;

    Vec4 in;
    in.x=_X;
    in.y=_Y;
    in.z=0.0f;
    in.w=1.0f;

    /* Map x and y from window coordinates */
    in.x = (in.x - 0) / 480;
    in.y = (in.y - 0) / 320;

    /* Map to range -1 to 1 */
    in.x = in.x * 2 - 1;
    in.y = in.y * 2 - 1;
    in.z = in.z * 2 - 1;

	// Transform the screen space pick ray into 3D space
	VECTOR4 out;
	MatrixVec4Multiply (out, in, mInv);
	out.x /= out.w;
	out.y /= out.w;
	out.z /= out.w;
	return Vec3(out.x, out.y, out.z);
}
