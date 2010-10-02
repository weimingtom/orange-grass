/*
 *  ogvertexbuffers.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGVERTEXBUFFERS_H_
#define OGVERTEXBUFFERS_H_

#include "Geometry.h"
#include "IOGStatistics.h"


class COGVertexBuffers
{
	COGVertexBuffers();

public:
	COGVertexBuffers (const SPODMesh* _pMesh);
	~COGVertexBuffers ();

	// apply buffers.
	void Apply () const;

	// render buffer geometry.
	void Render () const;

	// is indexed
	bool IsIndexed() const {return (m_pMesh->sFaces.pData != 0);}
	
private:

	unsigned int	m_VBO;
	unsigned int	m_IBO;
	unsigned int	m_NumVertices;
	const SPODMesh*	m_pMesh;
	IOGStatistics*	m_pStats;
};

#endif
