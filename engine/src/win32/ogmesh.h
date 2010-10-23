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

#include "IOGMesh.h"
#include "Geometry.h"
#include "Mathematics.h"
#include <vector>
#include <map>
#include "ogresource.h"
#include "IOGVertexBuffers.h"
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

	// Render mesh.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Render part of the mesh.
	virtual void RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame);

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const;

    // Get num animation frames.
	virtual unsigned int GetNumFrames () const;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

	// Get part AABB
	virtual const IOGAabb& GetAABB (unsigned int _Part) const {return m_AabbList[_Part];}

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const {return m_Faces;}

    // Get active point
    virtual bool GetActivePoint (Vec3& _Point, const std::string& _Alias, unsigned int _Frame);

protected:

	// calculate geometry
	virtual void CalculateGeometry ();

    // check if active point.
    bool IsActivePoint (unsigned int _Part);

protected:
	
	// Vertex Buffer Object (VBO) list
	std::vector<IOGVertexBuffers*>	m_BuffersList;
	
	// 3D Model
	CPVRTModelPOD*	m_pScene;

	// Bounds
	IOGAabb					m_AABB;
	std::vector<IOGAabb>	m_AabbList;
    std::vector<unsigned int>   m_PartList;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace>     m_Faces;

    struct ActPoint
    {
        Vec3 pos;
        unsigned int part;
    };
    std::map<std::string, ActPoint> m_ActivePoints;

    IOGRenderer*    m_pRenderer;

    unsigned int    m_NumParts;
};


#endif
