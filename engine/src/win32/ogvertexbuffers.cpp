/*
 *  ogvertexbuffers.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogvertexbuffers.h"


COGVertexBuffers::COGVertexBuffers () : m_pMesh(NULL),
										m_VBO(0),
										m_IBO(0)
{
}


COGVertexBuffers::~COGVertexBuffers ()
{
}


// initialize VBO and IBO.
COGVertexBuffers::COGVertexBuffers (const SPODMesh* _pMesh) :	m_pMesh(_pMesh),
																m_VBO(0),
																m_IBO(0)
{
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
}


// apply buffers.
void COGVertexBuffers::Apply () const
{
	// bind the VBO for the mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// bind the index buffer, won't hurt if the handle is 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	
	// Setup pointers
	glVertexPointer(3, VERTTYPEENUM, m_pMesh->sVertex.nStride, m_pMesh->sVertex.pData);
	if (m_pMesh->psUVW)
		glTexCoordPointer(2, VERTTYPEENUM, m_pMesh->psUVW[0].nStride, m_pMesh->psUVW[0].pData);
	glNormalPointer(VERTTYPEENUM, m_pMesh->sNormals.nStride, m_pMesh->sNormals.pData);
}


// render buffer geometry.
void COGVertexBuffers::Render () const
{
    if(m_pMesh->nNumStrips == 0)
    {
        if(IsIndexed())
        {
            // Indexed Triangle list
            glDrawElements(GL_TRIANGLES, m_pMesh->nNumFaces * 3, GL_UNSIGNED_SHORT, 0);
        }
        else
        {
            // Non-Indexed Triangle list
            glDrawArrays(GL_TRIANGLES, 0, m_pMesh->nNumFaces * 3);
        }
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
        }
    }
}
