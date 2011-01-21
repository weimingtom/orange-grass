/*
 *  ogvertexbuffers_gles20.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogvertexbuffers_gles20.h"
#ifdef GLES20

COGVertexBuffers_GLES20::COGVertexBuffers_GLES20 () : m_pMesh(NULL),
										m_VBO(0),
										m_IBO(0),
										m_NumVertices(0)
{
}


COGVertexBuffers_GLES20::~COGVertexBuffers_GLES20 ()
{
}


// initialize VBO and IBO.
COGVertexBuffers_GLES20::COGVertexBuffers_GLES20 (const SPODMesh* _pMesh) :	m_pMesh(_pMesh),
																m_VBO(0),
																m_IBO(0),
																m_NumVertices(0)
{
#ifdef USE_VBO
	if (m_pMesh->pInterleaved)
	{
		glGenBuffers(1, &m_VBO);
		unsigned int uiSize = m_pMesh->nNumVertex * m_pMesh->sVertex.nStride;
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, uiSize, m_pMesh->pInterleaved, GL_STATIC_DRAW);
	}
	else
	{
		return;
	}

	if(m_pMesh->sFaces.pData)
	{
		glGenBuffers(1, &m_IBO);
		unsigned int uiSize = PVRTModelPODCountIndices(*m_pMesh) * sizeof(GLshort);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, m_pMesh->sFaces.pData, GL_STATIC_DRAW);
	}

    glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#endif
	m_NumVertices = m_pMesh->nNumFaces * 3;
	m_pStats = GetStatistics();
}


// apply buffers.
void COGVertexBuffers_GLES20::Apply () const
{
#ifdef USE_VBO
	// bind the VBO for the mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// bind the index buffer, won't hurt if the handle is 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

	// Setup pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_pMesh->sVertex.nStride, m_pMesh->sVertex.pData);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_pMesh->sNormals.nStride, m_pMesh->sNormals.pData);
	if (m_pMesh->psUVW)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_pMesh->psUVW[0].nStride, m_pMesh->psUVW[0].pData);
#else
	// Setup pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_pMesh->sVertex.nStride, m_pMesh->pInterleaved);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_pMesh->sVertex.nStride, (void*)((char*)m_pMesh->pInterleaved + 12));
	if (m_pMesh->psUVW)
	{
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_pMesh->sVertex.nStride, (void*)((char*)m_pMesh->pInterleaved + 24));
	}
#endif
#ifdef STATISTICS
	m_pStats->AddVBOSwitch();
#endif
}


// render buffer geometry.
void COGVertexBuffers_GLES20::Render () const
{
    if(m_pMesh->nNumStrips == 0)
    {
        if(IsIndexed())
        {
#ifdef USE_VBO
            // Indexed Triangle list
            glDrawElements(GL_TRIANGLES, m_NumVertices, GL_UNSIGNED_SHORT, 0);
#else
            // Indexed Triangle list
            glDrawElements(GL_TRIANGLES, m_NumVertices, GL_UNSIGNED_SHORT, m_pMesh->sFaces.pData);
#endif
		}
        else
        {
            // Non-Indexed Triangle list
            glDrawArrays(GL_TRIANGLES, 0, m_NumVertices);
        }
#ifdef STATISTICS
		m_pStats->AddVertexCount(m_NumVertices, m_pMesh->nNumFaces);
		m_pStats->AddDrawCall();
#endif
    }
    else
    {
        for(unsigned int i = 0; i < m_pMesh->nNumStrips; ++i)
        {
            int offset = 0;
            if(IsIndexed())
            {
                // Indexed Triangle strips
                glDrawElements(GL_TRIANGLE_STRIP, m_pMesh->pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
            }
            else
            {
                // Non-Indexed Triangle strips
                glDrawArrays(GL_TRIANGLE_STRIP, offset, m_pMesh->pnStripLength[i]+2);
            }
            offset += m_pMesh->pnStripLength[i]+2;
#ifdef STATISTICS
			m_pStats->AddVertexCount(m_pMesh->pnStripLength[i]+2, 1);
			m_pStats->AddDrawCall();
#endif
        }
    }
}
#endif