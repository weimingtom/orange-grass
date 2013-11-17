/*
 *  ogdynvertexbuffers.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "OrangeGrass.h"
#include "ogdynvertexbuffers.h"


COGDynVertexBuffers::~COGDynVertexBuffers ()
{
    if (m_pIndexData)
        free(m_pIndexData);
    if (m_pVertexData)
        free(m_pVertexData);
    if (m_VBO != 0)
        glDeleteBuffers(1, &m_VBO);
    if (m_IBO != 0)
        glDeleteBuffers(1, &m_IBO);
}


COGDynVertexBuffers::COGDynVertexBuffers (unsigned int _NumIndices)
{
    m_pVertexData = NULL;
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);

    m_Stride = 36;
    m_NumIndices = _NumIndices;
    m_NumFaces = 0;

    unsigned int IBOSize = m_NumIndices * sizeof(GLshort);
    m_pIndexData = malloc(IBOSize);
    GLshort* pBuff = (GLshort*)m_pIndexData;
    for (size_t i = 0; i < m_NumIndices; i+=6)
    {
        pBuff[0] = i;
        pBuff[1] = i+1;
        pBuff[2] = i+2;
        pBuff[3] = i+2;
        pBuff[4] = i+3;
        pBuff[5] = i;
        pBuff += 6;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IBOSize, m_pIndexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    m_pStats = GetStatistics();
}


// apply buffers.
void COGDynVertexBuffers::Apply () const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(12));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(20));
#ifdef STATISTICS
    m_pStats->AddVBOSwitch();
#endif
}


// update buffer geometry.
void COGDynVertexBuffers::Update (const void* _pBuff, unsigned int _Size)
{
    if (_Size > 0)
    {
        if (m_pVertexData)
        {
            free(m_pVertexData);
            m_pVertexData = NULL;
        }
        m_pVertexData = malloc(_Size);
        memcpy(m_pVertexData, _pBuff, _Size);

        m_NumVertices = _Size / m_Stride;
        m_NumFaces = m_NumVertices / 4;
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, _Size, m_pVertexData, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}


// render buffer geometry.
void COGDynVertexBuffers::Render () const
{
    if (m_NumFaces > 0)
    {
        glDrawElements(GL_TRIANGLES, m_NumFaces * 3, GL_UNSIGNED_SHORT, 0);
#ifdef STATISTICS
        m_pStats->AddVertexCount(m_NumVertices, m_NumFaces);
        m_pStats->AddDrawCall();
#endif
    }
}
