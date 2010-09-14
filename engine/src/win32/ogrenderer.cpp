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
								m_pRT(NULL),
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
	OG_SAFE_DELETE(m_pRT);
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
	m_pRT = new COGRenderTarget();
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

	MatrixOrthoRH(m_mSMProjection, 32, 32, m_fZNear, m_fZFar, false);
	//MatrixPerspectiveFovRH(m_mSMProjection, m_fFOV, float(m_pRT->GetWidth())/float(m_pRT->GetHeight()), m_fZNear, m_fZFar, false);
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
		glAlphaFunc(GL_GREATER, 0.90f);
		glEnable(GL_ALPHA_TEST);
		glDisable(GL_CULL_FACE);
	    glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mSMProjection.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m_pCamera->GetViewMatrix().f);
		m_pLight->Enable(false);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_TRUE);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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
#ifdef USE_VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
   		glEnable(GL_TEXTURE_2D);
	    glEnable(GL_DEPTH_TEST);
		glDisable(GL_ALPHA_TEST);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		m_pRT->Apply();
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		break;
	}
}


// draw shadow quad.
void COGRenderer::DrawShadowQuad()
{
	StartRenderMode(OG_RENDERMODE_SPRITES);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	COGSprite::SprVert m_Vertices[4];
	float g_fHalfScrWidth = SCR_WIDTH / 2.0f;
	float g_fHalfScrHeight = SCR_HEIGHT / 2.0f;
	Vec2 _vPos = Vec2(0, 0);
	Vec2 _vSize = Vec2(256, 256);
	float fLeft = -g_fHalfScrWidth+_vPos.x;
	float fRight = -g_fHalfScrWidth+_vSize.x+_vPos.x;
	float fTop = g_fHalfScrHeight-_vSize.y-_vPos.y;
	float fBottom = g_fHalfScrHeight-_vPos.y;
	m_Vertices[0].p	= Vec2(fRight, fTop);	
	m_Vertices[0].t = Vec2(1, 0); 
	m_Vertices[1].p	= Vec2(fLeft, fTop);	
	m_Vertices[1].t = Vec2(0, 0); 
	m_Vertices[2].p	= Vec2(fRight, fBottom);	
	m_Vertices[2].t = Vec2(1, 1); 
	m_Vertices[3].p	= Vec2(fLeft, fBottom);	
	m_Vertices[3].t = Vec2(0, 1); 
	glBindTexture(GL_TEXTURE_2D, m_pRT->m_TextureId);
	glVertexPointer(2, GL_FLOAT, 16, m_Vertices);
	glTexCoordPointer(2, GL_FLOAT, 16, (void*)((char *)m_Vertices + 8));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisable (GL_BLEND); 
	FinishRenderMode();
}


// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
}
