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
#ifndef IOGVERTEXBUFFERS_H_
#define IOGVERTEXBUFFERS_H_


class IOGVertexBuffers
{
public:
    virtual ~IOGVertexBuffers () {};

    // apply buffers.
    virtual void Apply () const = 0;

    // render buffer geometry.
    virtual void Render () const = 0;

    // is indexed
    virtual bool IsIndexed() const = 0;

    // is dynamic
    virtual bool IsDynamic() const = 0;

    // number of vertices
    virtual unsigned int GetNumVertices () const = 0;

    // number of indices
    virtual unsigned int GetNumIndices () const = 0;

    // number of faces
    virtual unsigned int GetNumFaces () const = 0;

    // stride
    virtual unsigned int GetStride () const = 0;

    // vertex data
    virtual const void* GetVertexData () const = 0;

    // index data
    virtual const void* GetIndexData () const = 0;

    // map buffer geometry.
    virtual void Map () = 0;

    // unmap buffer geometry.
    virtual void Unmap () = 0;

    // update buffer geometry.
    virtual void Update (unsigned int _Offset, const void* _pBuff, unsigned int _Size) = 0;
};

#endif
