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

#include "OpenGL2.h"
#include "Geometry.h"


class COGVertexBuffers
{
	COGVertexBuffers();

public:
	COGVertexBuffers (const SPODMesh* _pMesh);
	~COGVertexBuffers ();

	// add rendering command.
	void Apply () const;

	// is indexed
	bool IsIndexed() const {return (m_IBO != 0);}
	
private:

	unsigned int	m_VBO;
	unsigned int	m_IBO;
	const SPODMesh*	m_pMesh;
};

#endif
