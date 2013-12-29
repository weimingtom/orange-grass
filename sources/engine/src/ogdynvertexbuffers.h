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


class COGDynVertexBuffers : public IOGVertexBuffers
{
public:
    COGDynVertexBuffers(unsigned int _NumFaces);
    virtual ~COGDynVertexBuffers ();

    // apply buffers.
    virtual void Apply () const;

    // map buffer geometry.
    virtual void Map ();

    // unmap buffer geometry.
    virtual void Unmap ();

    // update buffer geometry.
    virtual void Update (unsigned int _Offset, const void* _pBuff, unsigned int _Size);

    // render buffer geometry.
    virtual void Render () const;

    // is dynamic
    virtual bool IsDynamic() const { return true; }

    // is indexed
    virtual bool IsIndexed() const { return false; }

    // number of vertices
    virtual unsigned int GetNumVertices () const { return m_NumVertices; }

    // number of indices
    virtual unsigned int GetNumIndices () const { return 0; }

    // number of faces
    virtual unsigned int GetNumFaces () const { return m_NumFaces; }

    // stride
    virtual unsigned int GetStride () const { return m_Stride; }

    // vertex data
    virtual const void* GetVertexData () const { return m_pVertexData; }

    // index data
    virtual const void* GetIndexData () const { return NULL; }

private:

    unsigned int    m_VBO;
    unsigned int    m_NumVertices;
    unsigned int    m_NumFaces;
    unsigned int    m_Stride;
    unsigned int    m_MaxVertices;
    unsigned int    m_MaxFaces;
    unsigned int    m_MaxVBOSize;
    void*           m_pVertexData;

    IOGStatistics*  m_pStats;
};

#endif
