/*
 *  IOGVertexBuffers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
};

#endif
