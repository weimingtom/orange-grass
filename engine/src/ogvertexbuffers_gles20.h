/*
 *  ogvertexbuffers_gles20.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGVERTEXBUFFERS_GLES20_H_
#define OGVERTEXBUFFERS_GLES20_H_
#ifdef GLES20
#include "Geometry.h"
#include "IOGStatistics.h"
#include "IOGVertexBuffers.h"


class COGVertexBuffers_GLES20 : public IOGVertexBuffers
{
	COGVertexBuffers_GLES20();

public:
	COGVertexBuffers_GLES20 (const SPODMesh* _pMesh);
	virtual ~COGVertexBuffers_GLES20 ();

	// apply buffers.
	virtual void Apply () const;

	// render buffer geometry.
	virtual void Render () const;

	// is indexed
	virtual bool IsIndexed() const {return (m_pMesh->sFaces.pData != 0);}
	
private:

	unsigned int	m_VBO;
	unsigned int	m_IBO;
	unsigned int	m_NumVertices;
	const SPODMesh*	m_pMesh;
	IOGStatistics*	m_pStats;
};
#endif
#endif
