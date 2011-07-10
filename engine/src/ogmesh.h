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

#include "ogbasemesh.h"


class COGMesh : public COGBaseMesh
{
public:
	COGMesh ();
	virtual ~COGMesh();

	// Render mesh.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Render solid parts of the mesh.
	virtual void RenderSolidParts (const MATRIX& _mWorld, unsigned int _Frame);

	// Render transparent parts of the mesh.
	virtual void RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame, float _fSpin);

	// Render part of the mesh.
	virtual void RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame);

	// Check if has submeshes of the following type
	virtual bool HasSubmeshesOfType(SubMeshType _Type) const;

    // Get num renderable parts.
    virtual unsigned int GetNumRenderables () const { return m_NumParts; }

    // Get num animation frames.
	virtual unsigned int GetNumFrames () const;

	// Get part AABB
	virtual const IOGAabb& GetPartAABB (unsigned int _Part) const;

	// Get part's transformed OBB after applying animation
	virtual bool GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, const MATRIX& _mWorld) const;

    // Get active point
    virtual bool GetActivePoint (Vec3& _Point, const std::string& _Alias, unsigned int _Frame);

protected:

    // load sub-meshes
    virtual void LoadSubMeshes ();

    // unload sub-meshes
    virtual void UnloadSubMeshes ();

protected:

    struct ActPoint
    {
        Vec3 pos;
        unsigned int part;
    };

protected:

	std::vector<unsigned int>	m_SolidParts;
	std::vector<unsigned int>	m_TransparentParts;

    std::map<std::string, ActPoint> m_ActivePoints;

    IOGRenderer*    m_pRenderer;
};


#endif
