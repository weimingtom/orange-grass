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
