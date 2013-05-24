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
	virtual ~IOGVertexBuffers () {}

	// apply buffers.
	virtual void Apply () const = 0;

	// render buffer geometry.
	virtual void Render () const = 0;

	// is indexed
	virtual bool IsIndexed() const = 0;
};

#endif
