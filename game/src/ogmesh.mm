/*
 *  mesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#import "ogmesh.h"

COGMesh::COGMesh () :	m_pVBO (NULL),
						m_pIndexVBO (NULL),
						m_pScene (NULL)
{
	m_pScene = (CPVRTModelPOD*)malloc(sizeof(CPVRTModelPOD));
	memset(m_pScene, 0, sizeof(CPVRTModelPOD));
}


COGMesh::~COGMesh()
{
	if (m_pScene)
	{
		m_pScene->Destroy();
		free(m_pScene);
		m_pScene = NULL;
	}
	
	if (m_pVBO)
	{
		delete[] m_pVBO;
		m_pVBO = NULL;
	}
	
	if (m_pIndexVBO)
	{
		delete[] m_pIndexVBO;
		m_pIndexVBO = NULL;
	}
}


bool COGMesh::Load (const char* _pMeshFile)
{	
	if (!m_pScene->ReadFromFile(_pMeshFile))
	{
		return false;
	}
	
	m_pVBO = new GLuint[m_pScene->nNumMesh];
	m_pIndexVBO = new GLuint[m_pScene->nNumMesh];
	
	glGenBuffers(m_pScene->nNumMesh, m_pVBO);
	
	for(unsigned int i = 0; i < m_pScene->nNumMesh; ++i)
	{
		// Load vertex data into buffer object
		SPODMesh& curMesh = m_pScene->pMesh[i];
		unsigned int uiSize = curMesh.nNumVertex * curMesh.sVertex.nStride;
		
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[i]);
		glBufferData(GL_ARRAY_BUFFER, uiSize, curMesh.pInterleaved, GL_STATIC_DRAW);
		
		// Load index data into buffer object if available
		m_pIndexVBO[i] = 0;
		if(curMesh.sFaces.pData)
		{
			glGenBuffers(1, &m_pIndexVBO[i]);
			uiSize = PVRTModelPODCountIndices(curMesh) * sizeof(GLshort);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, curMesh.sFaces.pData, GL_STATIC_DRAW);
		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return true;
}


void COGMesh::Render (const MATRIX& _mView)
{
	for (unsigned int i=0; i<m_pScene->nNumMeshNode; ++i)
	{
		SPODNode* pNode = &m_pScene->pNode[i];
		
		// Gets the node model matrix
		MATRIX mWorld;
		m_pScene->GetWorldMatrix(mWorld, *pNode);
		
		// Multiply the view matrix by the model matrix to get the model-view matrix
		MATRIX mModelView;
		MatrixMultiply(mModelView, mWorld, _mView);
		glLoadMatrixf(mModelView.f);
				
		RenderObject(pNode->nIdx);
	}
}


void COGMesh::RenderObject(unsigned int _id)
{
	SPODMesh& Mesh = m_pScene->pMesh[_id];
	
	// bind the VBO for the mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[_id]);
	// bind the index buffer, won't hurt if the handle is 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[_id]);
	
	// Setup pointers
	glVertexPointer(3, VERTTYPEENUM, Mesh.sVertex.nStride, Mesh.sVertex.pData);
	if (Mesh.psUVW)
		glTexCoordPointer(2, VERTTYPEENUM, Mesh.psUVW[0].nStride, Mesh.psUVW[0].pData);
	glNormalPointer(VERTTYPEENUM, Mesh.sNormals.nStride, Mesh.sNormals.pData);
	
	if(Mesh.nNumStrips == 0)
	{
		if(m_pIndexVBO[_id])
		{
			// Indexed Triangle list
			glDrawElements(GL_TRIANGLES, Mesh.nNumFaces * 3, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			// Non-Indexed Triangle list
			glDrawArrays(GL_TRIANGLES, 0, Mesh.nNumFaces * 3);
		}
	}
	else
	{
		for(unsigned int i = 0; i < Mesh.nNumStrips; ++i)
		{
			int offset = 0;
			if(m_pIndexVBO[_id])
			{
				// Indexed Triangle strips
				glDrawElements(GL_TRIANGLE_STRIP, Mesh.pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
			}
			else
			{
				// Non-Indexed Triangle strips
				glDrawArrays(GL_TRIANGLE_STRIP, offset, Mesh.pnStripLength[i]+2);
			}
			offset += Mesh.pnStripLength[i]+2;
		}
	}
	
	// unbind the vertex buffers as we don't need them bound anymore
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
