/*
 *  oganimatedmesh.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "oganimatedmesh.h"


COGAnimatedMesh::COGAnimatedMesh () :	m_fFrame (0),
										m_pVBO (NULL),
										m_pIndexVBO (NULL),
										m_pScene (NULL)
{
	m_pScene = (CPVRTModelPOD*)malloc(sizeof(CPVRTModelPOD));
	memset(m_pScene, 0, sizeof(CPVRTModelPOD));
}


COGAnimatedMesh::~COGAnimatedMesh()
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


bool COGAnimatedMesh::Load (const char* _pMeshFile)
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


void COGAnimatedMesh::UpdateAnimation (int _ElapsedTime)
{
	if (m_pScene->nNumFrame > 0)
	{
		m_fFrame += VERTTYPEMUL(f2vt(_ElapsedTime), f2vt(DEMO_FRAME_RATE));
		
		while(m_fFrame > f2vt(m_pScene->nNumFrame-1))
			m_fFrame -= f2vt(m_pScene->nNumFrame-1);
		
		// Sets the scene animation to this frame
		m_pScene->SetFrame(m_fFrame);
	}
}


void COGAnimatedMesh::Render (const MATRIX& _mView)
{
	for(unsigned int iNode = 0; iNode < m_pScene->nNumMeshNode; ++iNode)
	{
		//Get the mesh node.
		SPODNode* pNode = &m_pScene->pNode[iNode];
		
		//Get the mesh that the mesh node uses.
		SPODMesh* pMesh = &m_pScene->pMesh[pNode->nIdx];
		
		// bind the VBO for the mesh
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[pNode->nIdx]);
		// bind the index buffer, won't hurt if the handle is 0
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[pNode->nIdx]);
		
		//If the mesh has bone weight data then we must be skinning.
		bool bSkinning = pMesh->sBoneWeight.pData != 0;
		
		// If the mesh is used for skining then set up the matrix palettes.
		if(bSkinning)
		{
			//Enable the matrix palette extension
			glEnable(GL_MATRIX_PALETTE_OES);
			
			// Enables the matrix palette stack extension, and apply subsequent
			// matrix operations to the matrix palette stack.
			glMatrixMode(GL_MATRIX_PALETTE_OES);
			
			MATRIX mBoneWorld;
			int	i32NodeID;
			
			// Iterate through all the bones in the batch
			for(int j = 0; j < pMesh->sBoneBatches.pnBatchBoneCnt[0]; ++j)
			{
				/*
				 Set the current matrix palette that we wish to change. An error
				 will be returned if the index (j) is not between 0 and
				 GL_MAX_PALETTE_MATRICES_OES. The value of GL_MAX_PALETTE_MATRICES_OES
				 can be retrieved using glGetIntegerv, the initial value is 9.
				 
				 GL_MAX_PALETTE_MATRICES_OES does not mean you need to limit
				 your character to 9 bones as you can overcome this limitation
				 by using bone batching which splits the mesh up into sub-meshes
				 which use only a subset of the bones.
				 */
				
				glCurrentPaletteMatrixOES(j);
				
				// Generates the world matrix for the given bone in this batch.
				i32NodeID = pMesh->sBoneBatches.pnBatches[j];
				m_pScene->GetBoneWorldMatrix(mBoneWorld, *pNode, m_pScene->pNode[i32NodeID]);
				
				// Multiply the bone's world matrix by the view matrix to put it in view space
				MatrixMultiply(mBoneWorld, mBoneWorld, _mView);
				
				// Load the bone matrix into the current palette matrix.
				glLoadMatrixf(mBoneWorld.f);
			}
		}
		else
		{
			//If we're not skinning then disable the matrix palette.
			glDisable(GL_MATRIX_PALETTE_OES);
		}
		
		//Switch to the modelview matrix.
		glMatrixMode(GL_MODELVIEW);
		//Push the modelview matrix
		glPushMatrix();
		
		//Get the world matrix for the mesh and transform the model view matrix by it.
		MATRIX worldMatrix;
		m_pScene->GetWorldMatrix(worldMatrix, *pNode);
		glMultMatrixf(worldMatrix.f);
		
		// Enable States
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		
		// If the mesh has uv coordinates then enable the texture coord array state
		if (pMesh->psUVW)
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		if(bSkinning)
		{
			//If we are skinning then enable the relevant states.
			glEnableClientState(GL_MATRIX_INDEX_ARRAY_OES);
			glEnableClientState(GL_WEIGHT_ARRAY_OES);
		}
		
		/* Set Data Pointers */
		// Used to display non interleaved geometry
		glVertexPointer(pMesh->sVertex.n, VERTTYPEENUM, pMesh->sVertex.nStride, pMesh->sVertex.pData);
		glNormalPointer(VERTTYPEENUM, pMesh->sNormals.nStride, pMesh->sNormals.pData);
		if (pMesh->psUVW)
			glTexCoordPointer(pMesh->psUVW[0].n, VERTTYPEENUM, pMesh->psUVW[0].nStride, pMesh->psUVW[0].pData);
		
		if(bSkinning)
		{
			//Set up the indexes into the matrix palette.
			glMatrixIndexPointerOES(pMesh->sBoneIdx.n, GL_UNSIGNED_BYTE, pMesh->sBoneIdx.nStride, pMesh->sBoneIdx.pData);
			glWeightPointerOES(pMesh->sBoneWeight.n, VERTTYPEENUM, pMesh->sBoneWeight.nStride, pMesh->sBoneWeight.pData);
		}
		
		// draw vertices
		if(pMesh->nNumStrips == 0)
		{
			if(m_pIndexVBO[iNode])
			{
				// Indexed Triangle list
				glDrawElements(GL_TRIANGLES, pMesh->nNumFaces * 3, GL_UNSIGNED_SHORT, 0);
			}
			else
			{
				// Non-Indexed Triangle list
				glDrawArrays(GL_TRIANGLES, 0, pMesh->nNumFaces * 3);
			}
		}
		else
		{
			for(unsigned int i = 0; i < pMesh->nNumStrips; ++i)
			{
				int offset = 0;
				if(m_pIndexVBO[iNode])
				{
					// Indexed Triangle strips
					glDrawElements(GL_TRIANGLE_STRIP, pMesh->pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
				}
				else
				{
					// Non-Indexed Triangle strips
					glDrawArrays(GL_TRIANGLE_STRIP, offset, pMesh->pnStripLength[i]+2);
				}
				offset += pMesh->pnStripLength[i]+2;
			}
		}
		
		/* Disable States */
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
		if(bSkinning)
		{
			glDisableClientState(GL_MATRIX_INDEX_ARRAY_OES);
			glDisableClientState(GL_WEIGHT_ARRAY_OES);
		}
		
		//Reset the modelview matrix back to what it was before we transformed by the mesh node.
		glPopMatrix();
	}
	
	//We are finished with the matrix pallete so disable it.
	glDisable(GL_MATRIX_PALETTE_OES);
	
	// unbind the vertex buffers as we don't need them bound anymore
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
