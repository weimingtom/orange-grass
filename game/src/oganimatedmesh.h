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

#include "IOGMesh.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "common.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "Mathematics.h"


class COGAnimatedMesh : public IOGMesh
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
	
public:
	// Animation frame
	VERTTYPE		m_fFrame;
	
	// Vertex Buffer Object (VBO) handles
	GLuint*			m_pVBO;
	GLuint*			m_pIndexVBO;
	
	// 3D Model
	CPVRTModelPOD*	m_pScene;	
};


#endif
