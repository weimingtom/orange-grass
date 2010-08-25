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


COGRenderer::COGRenderer ()
{
}


COGRenderer::~COGRenderer ()
{
}


// initialize renderer.
bool COGRenderer::Init ()
{
	return true;
}


// add rendering command.
void COGRenderer::SetTransform (const MATRIX& _mWorld)
{
	RenderCommand cmd;
	cmd.Type = RENDERCMD_SETTRANSFORM;
	cmd.mWorld = _mWorld;
	m_CommandBuffer.push_back(cmd);
}


// add rendering command.
void COGRenderer::SetTexture (IOGTexture* _pTexture)
{
	RenderCommand cmd;
	cmd.Type = RENDERCMD_SETTEXTURE;
	cmd.pTexture = _pTexture;
	m_CommandBuffer.push_back(cmd);
}


// add rendering command.
void COGRenderer::SetMaterial (IOGMaterial* _pMaterial)
{
	RenderCommand cmd;
	cmd.Type = RENDERCMD_SETMATERIAL;
	cmd.pMaterial = _pMaterial;
	m_CommandBuffer.push_back(cmd);
}


// add rendering command.
void COGRenderer::SetMesh (void* _pPODMesh,
						   unsigned int _hVBO,
						   unsigned int _hIBO)
{
	RenderCommand cmd;
	cmd.Type = RENDERCMD_SETMESH;
	cmd.pPODMesh = (SPODMesh*)_pPODMesh;
	cmd.hVBO = _hVBO;
	cmd.hIBO = _hIBO;
	m_CommandBuffer.push_back(cmd);
}


// render command buffer.
void COGRenderer::Render (const MATRIX& _mView)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	std::list<RenderCommand>::const_iterator iter = m_CommandBuffer.begin();
	for (; iter != m_CommandBuffer.end(); ++iter)
	{
		const RenderCommand& cmd = (*iter);
		switch (cmd.Type)
		{
		case RENDERCMD_SETTRANSFORM:
			{
				MATRIX mModelView;
				MatrixMultiply(mModelView, cmd.mWorld, _mView);
				glLoadMatrixf(mModelView.f);
			}
			break;

		case RENDERCMD_SETMATERIAL:
			{
				cmd.pMaterial->Apply();
			}
			break;

		case RENDERCMD_SETTEXTURE:
			{
				cmd.pTexture->Apply();
			}
			break;

		case RENDERCMD_SETMESH:
			{
				glBindBuffer(GL_ARRAY_BUFFER, cmd.hVBO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cmd.hIBO);
				glVertexPointer(3, VERTTYPEENUM, cmd.pPODMesh->sVertex.nStride, cmd.pPODMesh->sVertex.pData);
				if (cmd.pPODMesh->psUVW)
					glTexCoordPointer(2, VERTTYPEENUM, cmd.pPODMesh->psUVW[0].nStride, cmd.pPODMesh->psUVW[0].pData);
				glNormalPointer(VERTTYPEENUM, cmd.pPODMesh->sNormals.nStride, cmd.pPODMesh->sNormals.pData);

				if(cmd.pPODMesh->nNumStrips == 0)
				{
					if(cmd.hIBO)
					{
						// Indexed Triangle list
						glDrawElements(GL_TRIANGLES, cmd.pPODMesh->nNumFaces * 3, GL_UNSIGNED_SHORT, 0);
					}
					else
					{
						// Non-Indexed Triangle list
						glDrawArrays(GL_TRIANGLES, 0, cmd.pPODMesh->nNumFaces * 3);
					}
				}
				else
				{
					for(unsigned int i = 0; i < cmd.pPODMesh->nNumStrips; ++i)
					{
						int offset = 0;
						if(cmd.hIBO)
						{
							// Indexed Triangle strips
							glDrawElements(GL_TRIANGLE_STRIP, cmd.pPODMesh->pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
						}
						else
						{
							// Non-Indexed Triangle strips
							glDrawArrays(GL_TRIANGLE_STRIP, offset, cmd.pPODMesh->pnStripLength[i]+2);
						}
						offset += cmd.pPODMesh->pnStripLength[i]+2;
					}
				}
			}
			break;

		case RENDERCMD_NONE:
		default:
			break;
		}
	}
	m_CommandBuffer.clear();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
