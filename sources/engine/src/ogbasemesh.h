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

#include "IOGMath.h"
#include <vector>
#include <map>
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGRenderable.h"
#include "pvr/POD.h"


class COGBaseMesh : public IOGMesh, public COGResource
{
public:
	COGBaseMesh ();
	virtual ~COGBaseMesh();

    // Get list of all submeshes
    virtual const std::vector<OGSubMesh>& GetSubMeshes () const { return m_SubMeshes; }

    // Update submesh (for tools)
    virtual void UpdateSubMesh (unsigned int _Id, const OGSubMesh& _SubMesh);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const { return m_Faces; }

	// Get combined AABB
    virtual const IOGAabb& GetAABB () const { return m_AABB; }
	
	// Load mesh.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

    // Get ray intersection
    bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos);

protected:

	// calculate geometry
	void CalculateGeometry ();

	// convert mesh to an internal format
	void ConvertMesh ();

    // load sub-meshes
    virtual void LoadSubMeshes () = 0;

    // unload sub-meshes
    virtual void UnloadSubMeshes () = 0;

protected:

    struct InternalMesh
    {
        struct MeshVertex
        {
            OGVec3 Pos;
            OGVec3 Norm;
            OGVec2 Tex;
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
    std::vector<OGSubMesh> m_SubMeshes;

    // Geometry (for mapeditor mostly)
	std::vector<OGFace> m_Faces;

    // Number of visible mesh parts
    unsigned int m_NumParts;
};


#endif
