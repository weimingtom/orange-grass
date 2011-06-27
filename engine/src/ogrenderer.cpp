/*
 *  ogrenderer.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogrenderer.h"
#include "oglight.h"
#include "ogcamera.h"
#include "ogfog.h"
#include "ogmaterial.h"
#include "ogsprite.h"
#include "ogvertexbuffers.h"
#include "oggrutility.h"


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL),
								m_CurBlend(OG_BLEND_NO),
								m_pFog(NULL),
								m_pLightMgr(NULL),
								m_pCamera(NULL),
								m_pText(NULL),
								m_bLandscapeMode(false)
{
    m_bLightEnabled = false;
    m_bFogEnabled = false;

	m_pStats = GetStatistics();
}


COGRenderer::~COGRenderer ()
{
	m_ModelShader.Unload();
	m_SpriteShader.Unload();
	m_ColorEffectShader.Unload();
	m_TextShader.Unload();

    OG_SAFE_DELETE(m_pText);
    OG_SAFE_DELETE(m_pFog);
    OG_SAFE_DELETE(m_pLightMgr);
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

	m_pLightMgr = new COGLightMgr ();
	m_pCamera = new COGCamera ();
	m_pFog = new COGFog ();
	m_pText = new COGTextRenderer();

    IOGResourceMgr* pResMgr = GetResourceMgr();
    if (!m_ModelShader.Load(pResMgr->GetFullPath("Shaders/gles/Model.vsh"), pResMgr->GetFullPath("Shaders/gles/Model.fsh")))
        return false;
    if (!m_SpriteShader.Load(pResMgr->GetFullPath("Shaders/gles/Sprite.vsh"), pResMgr->GetFullPath("Shaders/gles/Sprite.fsh")))
        return false;
    if (!m_ColorEffectShader.Load(pResMgr->GetFullPath("Shaders/gles/ColorEffect.vsh"), pResMgr->GetFullPath("Shaders/gles/ColorEffect.fsh")))
        return false;
    if (!m_TextShader.Load(pResMgr->GetFullPath("Shaders/gles/Text.vsh"), pResMgr->GetFullPath("Shaders/gles/Text.fsh")))
        return false;

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

    for(int i=0; i<16; i++){m_mTextProj.f[i]=0;}
    m_mTextProj.f[10] = 1.0f; m_mTextProj.f[12] = -1.0f;
    m_mTextProj.f[13] = 1.0f; m_mTextProj.f[15] = 1.0f;

	m_bLandscapeMode = (GetGlobalVars()->GetIVar("landscape") == 1);

#ifdef WIN32
	MatrixOrthoRH(m_mOrthoProj, (float)m_Width, (float)m_Height, -1, 1, false);
    MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Width)/float(m_Height), m_fZNear, m_fZFar, false);
 	m_pText->SetTextures(_Width, _Height, false);
    m_mTextProj.f[0] = 2.0f/(m_Width);
    m_mTextProj.f[5] = -2.0f/(m_Height);
#else
	if (m_bLandscapeMode)
	{
		MatrixOrthoRH(m_mOrthoProj, (float)m_Height, (float)m_Width, -1, 1, true);
		MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Height)/float(m_Width), m_fZNear, m_fZFar, true);
 		m_pText->SetTextures(_Width, _Height, true);
		m_mTextProj.f[0] = 2.0f/(m_Height);
		m_mTextProj.f[5] = -2.0f/(m_Width);
	}
	else
	{
		MatrixOrthoRH(m_mOrthoProj, (float)m_Width, (float)m_Height, -1, 1, false);
		MatrixPerspectiveFovRH(m_mProjection, m_fFOV, float(m_Width)/float(m_Height), m_fZNear, m_fZFar, false);
 		m_pText->SetTextures(_Width, _Height, false);
		m_mTextProj.f[0] = 2.0f/(m_Width);
		m_mTextProj.f[5] = -2.0f/(m_Height);
	}
#endif

	m_pCamera->SetupViewport(m_mProjection, m_fFOV);
}


// Create vertex buffer for mesh.
IOGVertexBuffers* COGRenderer::CreateVertexBuffer (const void* _pMeshData)
{
	COGVertexBuffers* pVB = new COGVertexBuffers((const SPODMesh*)_pMeshData);
	return pVB;
}


// set model matrix.
void COGRenderer::SetModelMatrix (const MATRIX& _mModel)
{
    m_mWorld = _mModel;
}


// set view matrix.
void COGRenderer::SetViewMatrix (const MATRIX& _mView)
{
    m_mView = _mView;
}


// Enable scene light.
void COGRenderer::EnableLight (bool _bEnable)
{
	m_bLightEnabled = _bEnable;
}


// Enable scene fog.
void COGRenderer::EnableFog (bool _bEnable)
{
	m_bFogEnabled = _bEnable;
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
    if (_pMaterial != m_pCurMaterial)
    {
        m_pCurMaterial = _pMaterial;
    }
}


// add rendering command.
void COGRenderer::SetBlend (OGBlendType _Blend)
{
	if (m_CurBlend != _Blend)
	{
		m_CurBlend = _Blend;

		switch (m_CurBlend)
		{
		case OG_BLEND_NO:
			break;

		case OG_BLEND_SOLID:
			glDisable (GL_BLEND);
            m_pCurShader->EnableAlphaTest(false);
			//glDisable (GL_ALPHA_TEST); 
			break;

		case OG_BLEND_ALPHATEST:
			//glAlphaFunc(GL_GREATER, 0.2f);
			//glEnable(GL_ALPHA_TEST);
            m_pCurShader->EnableAlphaTest(true);
            glEnable (GL_BLEND); 
            glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			break;

		case OG_BLEND_ALPHABLEND:
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            m_pCurShader->EnableAlphaTest(false);
            //glDisable(GL_ALPHA_TEST);
			break;

		case OG_BLEND_ALPHAADD:
			glEnable (GL_BLEND); 
			glBlendFunc (GL_ONE, GL_ONE);
            m_pCurShader->EnableAlphaTest(false);
			//glDisable(GL_ALPHA_TEST);
			break;

		case OG_BLEND_ALPHAONE:
			glEnable (GL_BLEND); 
			glBlendFunc (GL_SRC_ALPHA,GL_ONE);
            m_pCurShader->EnableAlphaTest(false);
			//glDisable(GL_ALPHA_TEST);
			break;
		}
	}
}


// start rendering mode.
void COGRenderer::StartRenderMode(OGRenderMode _Mode)
{
	m_Mode = _Mode;
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
	    m_pCurShader = &m_ModelShader;
        glDisable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);
		SetViewMatrix(m_pCamera->GetViewMatrix());
        m_ModelShader.SetProjectionMatrix(m_mProjection);
        m_ModelShader.SetViewMatrix(m_mView);
		EnableLight(true);
		m_ModelShader.SetLightDir(m_pLightMgr->GetLight(0)->vPosition);
        m_ModelShader.SetFogParams(m_pFog->GetStart(), m_pFog->GetEnd(), m_pFog->GetColor());
        m_ModelShader.Setup();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;
		
	case OG_RENDERMODE_EFFECTS:
	    m_pCurShader = &m_ColorEffectShader;
		glDisable(GL_CULL_FACE);
        glDisable(GL_DEPTH_TEST);
		SetViewMatrix(m_pCamera->GetViewMatrix());
        m_ColorEffectShader.SetProjectionMatrix(m_mProjection);
        m_ColorEffectShader.SetViewMatrix(m_mView);
		EnableLight(false);
        m_ColorEffectShader.SetFogParams(m_pFog->GetStart(), m_pFog->GetEnd(), m_pFog->GetColor());
        m_ColorEffectShader.Setup();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_SPRITES:
	    m_pCurShader = &m_SpriteShader;
		SetBlend(OG_BLEND_ALPHABLEND);
        glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
        m_SpriteShader.SetProjectionMatrix(m_mOrthoProj);
		EnableLight(false);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
        m_SpriteShader.Setup();
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;

    case OG_RENDERMODE_TEXT:
	    m_pCurShader = &m_TextShader;
        m_TextShader.SetProjectionMatrix(m_mTextProj);
		SetBlend(OG_BLEND_ALPHATEST);
        m_TextShader.Setup();
        break;
	}
}


// finish rendering mode.
void COGRenderer::FinishRenderMode()
{
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_EFFECTS:
        glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND); 
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_SPRITES:
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;

	case OG_RENDERMODE_TEXT:
		m_pText->Flush();
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
		break;

    case OG_RENDERMODE_SHADOWMAP:
        break;
	}
}


// add rendering command.
void COGRenderer::RenderMesh (void* _pMesh)
{
    m_pCurShader->SetModelMatrix(m_mWorld);
    m_pCurShader->Apply();

	if ((IOGVertexBuffers*)_pMesh != m_pCurMesh)
    {
        m_pCurMesh = (IOGVertexBuffers*)_pMesh;
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
IOGLightMgr* COGRenderer::GetLightMgr ()
{
	return m_pLightMgr;
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


// Create material.
IOGMaterial* COGRenderer::CreateMaterial ()
{
	return new COGMaterial();
}


// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
	m_CurBlend = OG_BLEND_NO;
}


// Unproject screen coords.
Vec3 COGRenderer::UnprojectCoords (int _X, int _Y)
{
    float* pMV = m_mView.f;
    float* pP = m_mProjection.f;
	float x0, y0, z0;
#ifdef WIN32
	UnProject((float)_X, (float)(m_Height - _Y), 0.0f, pMV, pP, m_Width, m_Height, &x0, &y0, &z0);
#else
	if (m_bLandscapeMode)
	{
		UnProject((float)_Y, (float)_X, 0.0f, pMV, pP, m_Height, m_Width, &x0, &y0, &z0);
	}
	else
	{
		UnProject((float)_X, (float)(m_Height - _Y), 0.0f, pMV, pP, m_Width, m_Height, &x0, &y0, &z0);
	}
#endif    
    return Vec3(x0, y0, z0);
}


// Display string.
void COGRenderer::DisplayString (const Vec2& _vPos, 
								 float _fScale, 
								 unsigned int Colour, 
								 const char * const pszFormat, ...)
{
	va_list	args;
	static char	Text[5120+1];
	va_start(args, pszFormat);
	vsprintf(Text, pszFormat, args);
	va_end(args);

    m_pText->DisplayText(_vPos.x,_vPos.y,_fScale, Colour, Text);
}


// Draw effects buffer.
void COGRenderer::DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    m_pCurShader->SetModelMatrix(m_mWorld);
    m_pCurShader->Apply();

    // vertex pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 36, _pBuffer);
	// texture coord pointer
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 36, (void*)((char *)_pBuffer + 12));
	// color pointer
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 36, (void*)((char *)_pBuffer + 20));
    glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
	m_pStats->AddVertexCount(_NumVertices, 1);
	m_pStats->AddDrawCall();
	m_pStats->AddVBOSwitch();
#endif
}


// Draw sprite buffer.
void COGRenderer::DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    // vertex pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, _pBuffer);
	// texture coord pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 8));
	// color pointer
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 16));
	glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
	m_pStats->AddVertexCount(_NumVertices, 1);
	m_pStats->AddDrawCall();
	m_pStats->AddVBOSwitch();
#endif
}
