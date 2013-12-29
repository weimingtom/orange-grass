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
    if (m_pVertexData)
        free(m_pVertexData);
    if (m_VBO != 0)
        glDeleteBuffers(1, &m_VBO);
}


COGDynVertexBuffers::COGDynVertexBuffers (unsigned int _NumFaces)
{
    m_pVertexData = NULL;
    glGenBuffers(1, &m_VBO);

    m_Stride = 36;
    m_NumFaces = 0;
    m_NumVertices = 0;

    m_MaxFaces = _NumFaces;
    m_MaxVertices = (m_MaxFaces * 2) * 4;
    m_MaxVBOSize = m_Stride * m_MaxVertices;
    m_pVertexData = malloc(m_MaxVBOSize);

    m_pStats = GetStatistics();
}


// apply buffers.
void COGDynVertexBuffers::Apply () const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(0));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(12));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, m_Stride, (const void*)(20));
#ifdef STATISTICS
    m_pStats->AddVBOSwitch();
#endif
}


// map buffer geometry.
void COGDynVertexBuffers::Map ()
{
    m_NumVertices = 0;
    m_NumFaces = 0;
    //memset(m_pVertexData, 0, m_MaxVBOSize);
}


// unmap buffer geometry.
void COGDynVertexBuffers::Unmap ()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_NumVertices * m_Stride, m_pVertexData, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// update buffer geometry.
void COGDynVertexBuffers::Update (unsigned int _Offset, const void* _pBuff, unsigned int _Size)
{
    if (_Offset + _Size <= m_MaxVBOSize)
    {
        unsigned char* pDst = (unsigned char*)m_pVertexData + _Offset;
        memcpy(pDst, _pBuff, _Size);

        unsigned int numVertices = _Size / m_Stride;
        unsigned int numFaces = numVertices / 2;
        m_NumVertices += numVertices;
        m_NumFaces += numFaces;
    }
    else
    {
        m_NumVertices = m_NumVertices;
        return;
    }
}


// render buffer geometry.
void COGDynVertexBuffers::Render () const
{
    if (m_NumFaces > 0)
    {
        for (unsigned int i = 0; i < m_NumFaces / 2; ++i)
            glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4);
#ifdef STATISTICS
        m_pStats->AddVertexCount(m_NumVertices, m_NumFaces);
        m_pStats->AddDrawCall();
#endif
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
