/*
 *  ogrenderer_gles11.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogrenderer_gles11.h"
#include "ogtextrenderer_gles11.h"
#include "ogvertexbuffers_gles11.h"


COGRenderer_GLES11::COGRenderer_GLES11 ()
{
}


COGRenderer_GLES11::~COGRenderer_GLES11 ()
{
}


// initialize renderer.
bool COGRenderer_GLES11::Init ()
{
    COGRenderer::Init();
	m_pText = new COGTextRenderer_GLES11();
	return true;
}


// Create vertex buffer for mesh.
IOGVertexBuffers* COGRenderer_GLES11::CreateVertexBuffer (const void* _pMeshData)
{
	COGVertexBuffers_GLES11* pVB = new COGVertexBuffers_GLES11((const SPODMesh*)_pMeshData);
	return pVB;
}


// set model matrix.
void COGRenderer_GLES11::SetModelMatrix (const MATRIX& _mModel)
{
    MATRIX mModelView;
    MatrixMultiply(mModelView, _mModel, m_mView);
    glLoadMatrixf(mModelView.f);
}


// set view matrix.
void COGRenderer_GLES11::SetViewMatrix (const MATRIX& _mView)
{
    m_mView = _mView;
    glLoadMatrixf(m_mView.f);
}


// add rendering command.
void COGRenderer_GLES11::SetMaterial (IOGMaterial* _pMaterial)
{
    if (_pMaterial != m_pCurMaterial)
    {
        m_pCurMaterial = _pMaterial;
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, &m_pCurMaterial->GetAmbient().x);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &m_pCurMaterial->GetDiffuse().x);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, &m_pCurMaterial->GetSpecular().x);
    }
}


// Enable scene light.
void COGRenderer_GLES11::EnableLight (bool _bEnable)
{
	if (_bEnable)
	{
		glDisable(GL_COLOR_MATERIAL);
        unsigned int Id = 0;
        IOGLight* pLight = m_pLightMgr->GetLight(Id);
        while (pLight)
        {
            Vec4 vDir = Vec4(pLight->vPosition.x, pLight->vPosition.y, pLight->vPosition.z, 0.0f);
			switch (pLight->type)
			{
			case OG_LIGHT_DIRECTIONAL:
				{
					vDir.w = 0.0f;
				}
				break;

			case OG_LIGHT_POINT:
				{
					vDir.w = 1.0f;
				    OG_CLAMP(pLight->fIntensity, 1.0f, 100.0f);
			        float fAttentuation = 0.01f / pLight->fIntensity;

					glLightf(GL_LIGHT0+Id, GL_CONSTANT_ATTENUATION, 0.0f);
					glLightf(GL_LIGHT0+Id, GL_LINEAR_ATTENUATION, 0.0f);
					glLightf(GL_LIGHT0+Id, GL_QUADRATIC_ATTENUATION, fAttentuation);
				}
				break;
			}

            glLightfv(GL_LIGHT0+Id, GL_POSITION, (VERTTYPE*)&vDir);
			glLightfv(GL_LIGHT0+Id, GL_DIFFUSE, (VERTTYPE*)&pLight->vDiffuseColor);
			glLightfv(GL_LIGHT0+Id, GL_AMBIENT, (VERTTYPE*)&pLight->vAmbientColor);
			glLightfv(GL_LIGHT0+Id, GL_SPECULAR, (VERTTYPE*)&pLight->vSpecularColor);
            glEnable(GL_LIGHT0+Id);

            ++Id;
            pLight = m_pLightMgr->GetLight(Id);
        }
	}
	else
	{
		glDisable(GL_LIGHTING);

        unsigned int Id = 0;
        while (m_pLightMgr->GetLight(Id))
        {
    		glDisable(GL_LIGHT0+Id);
            ++Id;
        }
    }
}


// Enable scene fog.
void COGRenderer_GLES11::EnableFog (bool _bEnable)
{
    if (_bEnable)
    {
        const float* pColor = (const float*)&m_pFog->GetColor();
        glFogf(GL_FOG_MODE, GL_LINEAR);
        glHint(GL_FOG_HINT, GL_DONT_CARE);
        glFogfv(GL_FOG_COLOR, pColor);
        glFogf(GL_FOG_START, m_pFog->GetStart());
        glFogf(GL_FOG_END, m_pFog->GetEnd());
        glFogf(GL_FOG_DENSITY, m_pFog->GetDensity());
        glEnable(GL_FOG);
    }
    else
    {
		glDisable(GL_FOG);
    }
}


// start rendering mode.
void COGRenderer_GLES11::StartRenderMode(OGRenderMode _Mode)
{
	m_Mode = _Mode;
	switch(m_Mode)
	{
	case OG_RENDERMODE_GEOMETRY:
		glDisableClientState(GL_COLOR_ARRAY);
		//glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_ALPHA, GL_REPLACE);
		//glTexEnvi(GL_TEXTURE_ENV, GL_SRC0_ALPHA, GL_TEXTURE);
		//glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_ALPHA, GL_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	    glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mProjection.f);
		glMatrixMode(GL_MODELVIEW);
		SetViewMatrix(m_pCamera->GetViewMatrix());
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		break;
		
	case OG_RENDERMODE_EFFECTS:
	    glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mProjection.f);
		glMatrixMode(GL_MODELVIEW);
		SetViewMatrix(m_pCamera->GetViewMatrix());
        glDisable(GL_DEPTH_TEST);
        glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);	
		break;
	
	case OG_RENDERMODE_SPRITES:
		SetBlend(OG_BLEND_ALPHABLEND);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(m_mOrthoProj.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);	
		break;

	case OG_RENDERMODE_TEXT:
		SetBlend(OG_BLEND_ALPHATEST);
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;
	}
}


// finish rendering mode.
void COGRenderer_GLES11::FinishRenderMode()
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
        glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND); 
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);	
		glDisableClientState(GL_COLOR_ARRAY);
		break;
	
	case OG_RENDERMODE_SPRITES:
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		break;

	case OG_RENDERMODE_TEXT:
		m_pText->Flush();
		glDisable(GL_BLEND); 
		glEnable(GL_DEPTH_TEST);
		break;

	case OG_RENDERMODE_SHADOWMAP:
		break;
	}
}


// Draw effects buffer.
void COGRenderer_GLES11::DrawEffectBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
    glVertexPointer(3, GL_FLOAT, 36, _pBuffer);
	glTexCoordPointer(2, GL_FLOAT, 36, (void*)((char *)_pBuffer + 12));
	glColorPointer(4, GL_FLOAT, 36, (void*)((char *)_pBuffer + 20));
    glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
	m_pStats->AddVertexCount(_NumVertices, 1);
	m_pStats->AddDrawCall();
	m_pStats->AddVBOSwitch();
#endif
}


// Draw sprite buffer.
void COGRenderer_GLES11::DrawSpriteBuffer (void* _pBuffer, int _StartId, int _NumVertices)
{
	glVertexPointer(2, GL_FLOAT, 32, _pBuffer);
	glTexCoordPointer(2, GL_FLOAT, 32, (void*)((char *)_pBuffer + 8));
	glColorPointer(4, GL_FLOAT, 32, (void*)((char *)_pBuffer + 16));
	glDrawArrays(GL_TRIANGLE_STRIP, _StartId, _NumVertices);

#ifdef STATISTICS
	m_pStats->AddVertexCount(_NumVertices, 1);
	m_pStats->AddDrawCall();
	m_pStats->AddVBOSwitch();
#endif
}
