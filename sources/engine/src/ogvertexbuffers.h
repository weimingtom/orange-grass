/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#ifndef OGVERTEXBUFFERS_H_
#define OGVERTEXBUFFERS_H_
#include "IOGStatistics.h"
#include "IOGVertexBuffers.h"


class COGVertexBuffers : public IOGVertexBuffers
{
private:
    COGVertexBuffers();

public:
    COGVertexBuffers (
        const void* _pVertexData, 
        unsigned int _NumVertices,
        unsigned int _NumFaces,
        unsigned int _Stride, 
        const void* _pIndexData, 
        unsigned int _NumIndices);

    virtual ~COGVertexBuffers ();

    // apply buffers.
    virtual void Apply () const;

    // render buffer geometry.
    virtual void Render () const;

    // is indexed
    virtual bool IsIndexed() const { return (m_pIndexData != NULL); }

    // number of vertices
    virtual unsigned int GetNumVertices () const { return m_NumVertices; }

    // number of indices
    virtual unsigned int GetNumIndices () const { return m_NumIndices; }

    // number of faces
    virtual unsigned int GetNumFaces () const { return m_NumFaces; }

    // stride
    virtual unsigned int GetStride () const { return m_Stride; }

    // vertex data
    virtual const void* GetVertexData () const { return m_pVertexData; }

    // index data
    virtual const void* GetIndexData () const { return m_pIndexData; }

    // map buffer geometry.
    virtual void Map () {}

    // unmap buffer geometry.
    virtual void Unmap () {}

    // update buffer geometry.
    virtual void Update (unsigned int _Offset, const void* _pBuff, unsigned int _Size) {}

    // is dynamic
    virtual bool IsDynamic() const { return false; }

private:

    unsigned int    m_VBO;
    unsigned int    m_IBO;
    unsigned int    m_NumVertices;
    unsigned int    m_NumIndices;
    unsigned int    m_NumFaces;
    unsigned int    m_Stride;
    void*           m_pVertexData;
    void*           m_pIndexData;

    IOGStatistics*  m_pStats;
};

#endif
