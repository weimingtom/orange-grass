/*
 *  oganimatedmesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 14.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGANIMATEDMESH_H_
#define OGANIMATEDMESH_H_

#include "OpenGL2.h"
#include "IOGMesh.h"
#include "Geometry.h"
#include "common.h"
#include "Mathematics.h"
#include <vector>
#include "ogresource.h"


class COGAnimatedMesh : public IOGMesh, COGResource
{
public:
	COGAnimatedMesh ();
	virtual ~COGAnimatedMesh();
	
	// Load mesh.
	virtual bool Load (const char* _pMeshFile);
	
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime);
	
	// Render mesh.
	virtual void Render (const MATRIX& _mView);

	// Get number of parts
	virtual int GetNumParts () const;

	// Get AABB for the specified part
	virtual const IOGAabb& GetAABB ( int _part ) const;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

public:
	// Animation frame
	VERTTYPE		m_fFrame;
	
	// Vertex Buffer Object (VBO) handles
	GLuint*			m_pVBO;
	GLuint*			m_pIndexVBO;
	
	// 3D Model
	CPVRTModelPOD*	m_pScene;	

	// Bounds
	std::vector<IOGAabb>	m_AABBs;
	IOGAabb					m_CombinedAABB;
};


#endif
