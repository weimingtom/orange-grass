/*
 *  ogscenemesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSCENEMESH_H_
#define OGSCENEMESH_H_

#include "Geometry.h"
#include "Mathematics.h"
#include <vector>
#include <map>
#include "ogresource.h"
#include "IOGVertexBuffers.h"
#include "IOGRenderer.h"
#include "IOGRenderable.h"


class COGSceneMesh : public COGResource
{
public:
	COGSceneMesh ();
	virtual ~COGSceneMesh();
	
	// Load mesh.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// Render parts of the mesh.
	void RenderTerraParts (const MATRIX& _mWorld, const IOGFrustum& _frustum);

	// Render parts of the mesh.
	void RenderSolidParts (const MATRIX& _mWorld, const IOGFrustum& _frustum);

	// Render parts of the mesh.
	void RenderTransparentParts (const MATRIX& _mWorld, const IOGFrustum& _frustum);

	// Get combined AABB
	const IOGAabb& GetAABB () const;

    // Get ray intersection
    bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    const std::vector<OGFace>& GetGeometry () const {return m_Faces;}

protected:

	// calculate geometry
	void CalculateGeometry ();

	// get scene mesh type.
	SceneMeshType GetSceneMeshType (unsigned int _Id);

protected:

    struct SceneMesh
    {
        unsigned int        part;
        SceneMeshType       type;
        IOGAabb*            aabb;
        IOGVertexBuffers*   buffer;
    };

protected:
	
	// 3D Model
	CPVRTModelPOD*				m_pScene;

	// Bounds
	IOGAabb						m_AABB;

    std::vector<SceneMesh>		m_SubMeshes;

	typedef std::vector<unsigned int>	PartsList;
	PartsList	m_TerraParts;
	PartsList	m_SolidParts;
	PartsList	m_TransparentParts;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace>			m_Faces;

    IOGRenderer*				m_pRenderer;

    unsigned int				m_NumParts;
};


#endif
