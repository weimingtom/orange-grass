/*
 *  ogbasemesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGBASEMESH_H_
#define OGBASEMESH_H_

#include "Geometry.h"
#include "Mathematics.h"
#include <vector>
#include <map>
#include "ogresource.h"
#include "IOGVertexBuffers.h"
#include "IOGRenderer.h"
#include "IOGRenderable.h"


class COGBaseMesh : public COGResource
{
public:
	COGBaseMesh ();
	virtual ~COGBaseMesh();
	
	// Load mesh.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// Get combined AABB
    virtual const IOGAabb& GetAABB () const { return m_AABB; }

	// Get all submesh AABBs
    void GetAllAABBs (std::vector<IOGAabb*>& _aabbs);

    // Get ray intersection
    bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    const std::vector<OGFace>& GetGeometry () const { return m_Faces; }

protected:

	// calculate geometry
	void CalculateGeometry ();

	// convert mesh to an internal format
	void ConvertMesh ();

    // load sub-meshes
    virtual void LoadSubMeshes () = 0;

    // unload sub-meshes
    virtual void UnloadSubMeshes () = 0;

    // get sub-mesh type.
    SubMeshType GetSubMeshType (unsigned int _Id);

protected:

    struct SubMesh
    {
        unsigned int        part;
        SubMeshType         type;
        IOGAabb*            aabb;
        IOGVertexBuffers*   buffer;
    };

    struct InternalMesh
    {
        struct MeshVertex
        {
            Vec3 Pos;
            Vec3 Norm;
            Vec2 Tex;
        };
        MeshVertex* pVertices;
        unsigned int* pFaces;
    };

protected:
	
	// 3D Model
	CPVRTModelPOD* m_pScene;

	// Combined bounds
	IOGAabb m_AABB;

    // SubMeshes list
    std::vector<SubMesh> m_SubMeshes;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace> m_Faces;

    // Number of visible mesh parts
    unsigned int m_NumParts;
};


#endif
