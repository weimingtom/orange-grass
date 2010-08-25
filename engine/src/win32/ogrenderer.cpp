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


COGRenderer::COGRenderer () :   m_pCurTexture(NULL),
                                m_pCurMaterial(NULL),
                                m_pCurMesh(NULL)
{
}


COGRenderer::~COGRenderer ()
{
}


// initialize renderer.
bool COGRenderer::Init ()
{
    Reset();
	return true;
}


// add rendering command.
void COGRenderer::SetTexture (IOGTexture* _pTexture)
{
    if (_pTexture != m_pCurTexture)
    {
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


// start rendering meshes.
void COGRenderer::StartRenderingMeshes()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}


// finish rendering meshes.
void COGRenderer::FinishRenderingMeshes()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

	
// reset renderer pipeline.
void COGRenderer::Reset ()
{
    m_pCurTexture = NULL;
    m_pCurMaterial = NULL;
    m_pCurMesh = NULL;
}
