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
#include "ogrenderer_gles20.h"


COGRenderer_GLES20::COGRenderer_GLES20 ()
{
    m_bLightEnabled = false;
    m_bFogEnabled = false;
}


COGRenderer_GLES20::~COGRenderer_GLES20 ()
{
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

	return true;
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
        glEnable(GL_CULL_FACE);
	    glEnable(GL_DEPTH_TEST);
		SetViewMatrix(m_pCamera->GetViewMatrix());
        m_ModelShader.SetProjectionMatrix(m_mProjection);
        m_ModelShader.SetViewMatrix(m_mView);
		EnableLight(true);
        m_ModelShader.SetLightDir(m_pLight->GetDirection());
        m_ModelShader.SetFogParams(m_pFog->GetStart(), m_pFog->GetEnd(), m_pFog->GetColor());
        m_ModelShader.Setup();
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		break;
		
	case OG_RENDERMODE_EFFECTS:
	    m_pCurShader = &m_ColorEffectShader;
		glDisable(GL_CULL_FACE);
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
		glAlphaFunc(GL_GREATER, 0.1f);
		glDisable(GL_DEPTH_TEST);
	    glDisable(GL_CULL_FACE);
        m_SpriteShader.SetProjectionMatrix(m_mOrthoProj);
		EnableLight(false);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
        m_SpriteShader.Setup();
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;

    case OG_RENDERMODE_TEXT:
		glAlphaFunc(GL_GREATER, 0.1f);
		glDisable(GL_DEPTH_TEST);
	    glDisable(GL_CULL_FACE);
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
		glDisable(GL_BLEND); 
	    glEnable(GL_CULL_FACE);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		break;
	
	case OG_RENDERMODE_SPRITES:
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
	    glEnable(GL_CULL_FACE);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		m_pText->Flush();
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
}


// Draw sprite buffer.
void COGRenderer_GLES20::DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    // vertex pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, _pBuffer);
	// texture coord pointer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (void*)((char *)_pBuffer + 8));
	glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);
}
