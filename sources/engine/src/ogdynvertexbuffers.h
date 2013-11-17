/*
 *  ogdynvertexbuffers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGDYNVERTEXBUFFERS_H_
#define OGDYNVERTEXBUFFERS_H_
#include "IOGStatistics.h"
#include "IOGVertexBuffers.h"


class COGDynVertexBuffers : public IOGDynVertexBuffers
{
public:
    COGDynVertexBuffers(unsigned int _NumIndices);
    virtual ~COGDynVertexBuffers ();

    // apply buffers.
    virtual void Apply () const;

    // update buffer geometry.
    virtual void Update (const void* _pBuff, unsigned int _Size);

    // render buffer geometry.
    virtual void Render () const;

private:

    unsigned int    m_VBO;
    unsigned int    m_IBO;
    unsigned int    m_NumVertices;
    unsigned int    m_NumIndices;
    unsigned int    m_NumFaces;
    unsigned int    m_Stride;
    void*           m_pIndexData;
    void*           m_pVertexData;

    IOGStatistics*  m_pStats;
};

#endif
