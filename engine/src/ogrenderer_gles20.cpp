/*
 *  ogrenderer_gles20.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#ifdef GLES20
#include "ogrenderer_gles20.h"
#include "ogtextrenderer_gles20.h"
#include "ogvertexbuffers_gles20.h"
#include "ogsprite.h"


COGRenderer_GLES20::COGRenderer_GLES20 ()
{
    m_bLightEnabled = false;
    m_bFogEnabled = false;
    m_pRT = NULL;
}


COGRenderer_GLES20::~COGRenderer_GLES20 ()
{
    OG_SAFE_DELETE(m_pRT);
}


// initialize renderer.
bool COGRenderer_GLES20::Init ()
{
    COGRenderer::Init();
    IOGResourceMgr* pResMgr = GetResourceMgr();
    if (!m_ModelShader.Load(pResMgr->GetFullPath("Shaders/Model.vsh"), pResMgr->GetFullPath("Shaders/Model.fsh")))
        return false;
    if (!m_SpriteShader.Load(pResMgr->GetFullPath("Shaders/Sprite.vsh"), pResMgr->GetFullPath("Shaders/Sprite.fsh")))
        return false;
    if (!m_ColorEffectShader.Load(pResMgr->GetFullPath("Shaders/ColorEffect.vsh"), pResMgr->GetFullPath("Shaders/ColorEffect.fsh")))
        return false;
    if (!m_TextShader.Load(pResMgr->GetFullPath("Shaders/Text.vsh"), pResMgr->GetFullPath("Shaders/Text.fsh")))
        return false;
    if (!m_ShadowModelShader.Load(pResMgr->GetFullPath("Shaders/ShadowModel.vsh"), pResMgr->GetFullPath("Shaders/ShadowModel.fsh")))
        return false;

	MatrixOrthoRH(m_mSMProjection, 256.0f, 256.0f, 1, 400.0f, true);
    m_pRT = new COGRenderTarget();

	m_pText = new COGTextRenderer_GLES20();

	return true;
}


// Create vertex buffer for mesh.
IOGVertexBuffers* COGRenderer_GLES20::CreateVertexBuffer (const void* _pMeshData)
{
	COGVertexBuffers_GLES20* pVB = new COGVertexBuffers_GLES20((const SPODMesh*)_pMeshData);
	return pVB;
}


// set model matrix.
void COGRenderer_GLES20::SetModelMatrix (const MATRIX& _mModel)
{
    m_mWorld = _mModel;
}


// set view matrix.
void COGRenderer_GLES20::SetViewMatrix (const MATRIX& _mView)
{
    m_mView = _mView;
}


// Enable scene light.
void COGRenderer_GLES20::EnableLight (bool _bEnable)
{
	m_bLightEnabled = _bEnable;
}


// Enable scene fog.
void COGRenderer_GLES20::EnableFog (bool _bEnable)
{
	m_bFogEnabled = _bEnable;
}


// start rendering mode.
void COGRenderer_GLES20::StartRenderMode(OGRenderMode _Mode)
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
		//glEnable (GL_BLEND); 
		//glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glDisable(GL_ALPHA_TEST);
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);
		SetBlend(OG_BLEND_ALPHABLEND);
		glDisable(GL_DEPTH_TEST);
        m_SpriteShader.SetProjectionMatrix(m_mOrthoProj);
		EnableLight(false);
        m_SpriteShader.Setup();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;

	case OG_RENDERMODE_SHADOWMAP:
	    m_pCurShader = &m_ShadowModelShader;
        glDisable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);
		SetViewMatrix(m_pCamera->GetViewMatrix());
        m_ShadowModelShader.SetProjectionMatrix(m_mSMProjection);
        m_ShadowModelShader.SetViewMatrix(m_mView);
		EnableLight(false);
        m_ShadowModelShader.Setup();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;

    case OG_RENDERMODE_TEXT:
	    m_pCurShader = &m_TextShader;
        m_TextShader.SetProjectionMatrix(m_mTextProj);
		glAlphaFunc(GL_GREATER, 0.1f);
		glDisable(GL_DEPTH_TEST);
	    glDisable(GL_CULL_FACE);
        m_TextShader.Setup();
        break;
	}
}


// finish rendering mode.
void COGRenderer_GLES20::FinishRenderMode()
{
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
#ifdef USE_VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_EFFECTS:
        glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND); 
	    glEnable(GL_CULL_FACE);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_SPRITES:
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
	    //glEnable(GL_CULL_FACE);
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
#ifdef USE_VBO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
        m_pRT->Apply();
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
        break;
	}
}


// add rendering command.
void COGRenderer_GLES20::RenderMesh (void* _pMesh)
{
    m_pCurShader->SetModelMatrix(m_mWorld);
    m_pCurShader->Apply();
    COGRenderer::RenderMesh(_pMesh);
}


// Draw effects buffer.
void COGRenderer_GLES20::DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices)
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
void COGRenderer_GLES20::DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    // vertex pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, _pBuffer);
	// texture coord pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 8));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (void*)((char *)_pBuffer + 16));
	glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
	m_pStats->AddVertexCount(_NumVertices, 1);
	m_pStats->AddDrawCall();
	m_pStats->AddVBOSwitch();
#endif
}


// Draw shadow texture.
void COGRenderer_GLES20::DrawShadowTexture ()
{
	int m_HalfScrWidth = GetGlobalVars()->GetIVar("view_width") / 2;
	int m_HalfScrHeight = GetGlobalVars()->GetIVar("view_height") / 2;
	float fLeft = (float)-m_HalfScrWidth;
	float fRight = (float)-m_HalfScrWidth+256.0f;
	float fTop = (float)m_HalfScrHeight-256.0f;
	float fBottom = (float)m_HalfScrHeight;

    COGSprite::SprVert Vertices[4];
	Vertices[0].p = Vec2(fRight, fTop);	
	Vertices[0].t = Vec2(1, 0); 
	Vertices[0].c = Vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	Vertices[1].p = Vec2(fLeft, fTop);	
	Vertices[1].t = Vec2(0, 0); 
	Vertices[1].c = Vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	Vertices[2].p = Vec2(fRight, fBottom);	
	Vertices[2].t = Vec2(1, 1); 
	Vertices[2].c = Vec4(1.0f, 1.0f, 1.0f, 1.0f); 
	Vertices[3].p = Vec2(fLeft, fBottom);	
	Vertices[3].t = Vec2(0, 1); 
	Vertices[3].c = Vec4(1.0f, 1.0f, 1.0f, 1.0f); 

    glBindTexture(GL_TEXTURE_2D, m_pRT->m_TextureId);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 32, Vertices);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 32, (void*)((char *)Vertices + 8));
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 32, (void*)((char *)Vertices + 16));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

#endif