/*
 *  ogvertexbuffers.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogvertexbuffers.h"


COGVertexBuffers::~COGVertexBuffers ()
{
    if (m_pVertexData)
        free(m_pVertexData);
    if (m_pIndexData)
        free(m_pIndexData);
    if (m_VBO != 0)
        glDeleteBuffers(1, &m_VBO);
    if (m_IBO != 0)
        glDeleteBuffers(1, &m_IBO);
}


COGVertexBuffers::COGVertexBuffers (
    const void* _pVertexData, 
    unsigned int _NumVertices, 
    unsigned int _NumFaces,
    unsigned int _Stride, 
    const void* _pIndexData, 
    unsigned int _NumIndices)
{
    m_NumVertices = _NumVertices;
    m_Stride = _Stride;
    m_NumIndices = _NumIndices;
    m_NumFaces = _NumFaces;

    unsigned int VBOSize = m_NumVertices * m_Stride;
    m_pVertexData = malloc(VBOSize);
    memcpy(m_pVertexData, _pVertexData, VBOSize);
    //m_pVertexData = _pVertexData;

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, VBOSize, m_pVertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(_pIndexData)
    {
        unsigned int IBOSize = _NumIndices * sizeof(GLshort);
        m_pIndexData = malloc(IBOSize);
        memcpy(m_pIndexData, _pIndexData, IBOSize);
        //m_pIndexData = _pIndexData;

        glGenBuffers(1, &m_IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBOSize, m_pIndexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    m_pStats = GetStatistics();
}


// apply buffers.
void COGVertexBuffers::Apply () const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(0+sizeof(float)*3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(0+sizeof(float)*6));
#ifdef STATISTICS
    m_pStats->AddVBOSwitch();
#endif
}


// render buffer geometry.
void COGVertexBuffers::Render () const
{
    if(IsIndexed())
    {
        glDrawElements(GL_TRIANGLES, m_NumFaces * 3, GL_UNSIGNED_SHORT, 0);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, m_NumFaces * 3);
    }
#ifdef STATISTICS
    m_pStats->AddVertexCount(m_NumVertices, m_NumFaces);
    m_pStats->AddDrawCall();
#endif
}
