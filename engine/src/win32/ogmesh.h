/*
 *  ogmesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMESH_H_
#define OGMESH_H_

#include "OpenGL2.h"
#include "IOGMesh.h"
#include "Geometry.h"
#include "Mathematics.h"
#include <vector>
#include "ogresource.h"
#include "ogvertexbuffers.h"
#include "IOGRenderer.h"


class COGMesh : public IOGMesh, public COGResource
{
public:
	COGMesh ();
	virtual ~COGMesh();
	
	// Load mesh.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();
	
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) {}

	// Render mesh.
	virtual void Render (const MATRIX& _mView);

	// Render.
	virtual void Render (const MATRIX& _mView, unsigned int _Part);

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const {return m_Faces;}

private:

	// calculate geometry
	void CalculateGeometry ();

private:
	
	// Vertex Buffer Object (VBO) list
	std::vector<COGVertexBuffers*>	m_BuffersList;
	
	// 3D Model
	CPVRTModelPOD*	m_pScene;

	// Bounds
	IOGAabb			m_AABB;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace>     m_Faces;

    IOGRenderer*    m_pRenderer;
};


#endif
