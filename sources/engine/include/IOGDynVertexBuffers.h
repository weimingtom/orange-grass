/*
 *  IOGDynVertexBuffers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IODYNGVERTEXBUFFERS_H_
#define IODYNGVERTEXBUFFERS_H_


class IOGDynVertexBuffers
{
public:
    virtual ~IOGDynVertexBuffers () {};

    // apply buffers.
    virtual void Apply () const = 0;

    // update buffer geometry.
    virtual void Update (const void* _pBuff, unsigned int _Size) = 0;

    // render buffer geometry.
    virtual void Render () const = 0;
};

#endif
