/*
 *  mesh.h
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


class COGMesh : public IOGMesh, public COGResource
{
public:
	COGMesh ();
	virtual ~COGMesh();
	
	// Load mesh.
	virtual bool Load ();
	
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime) {}

	// Render mesh.
	virtual void Render (const MATRIX& _mView);

	// Get number of parts
	virtual int GetNumParts () const;

	// Get AABB for the specified part
	virtual const IOGAabb& GetAABB ( int _part ) const;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const {return m_Faces;}

private:
	
	// render sub-mesh
	void RenderObject(unsigned int _id);

	// calculate bounds
	void CalculateBounds ();

	// calculate geometry
	void CalculateGeometry ();

private:
	
	// Vertex Buffer Object (VBO) handles
	GLuint*			m_pVBO;
	GLuint*			m_pIndexVBO;
	
	// 3D Model
	CPVRTModelPOD*	m_pScene;

	// Bounds
	std::vector<IOGAabb>	m_AABBs;
	IOGAabb					m_CombinedAABB;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace>     m_Faces;

};


#endif
