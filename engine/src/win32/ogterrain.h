/*
 *  ogterrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTERRAIN_H_
#define OGTERRAIN_H_

#include "OpenGL2.h"
#include "IOGTerrain.h"
#include "IOGMaterial.h"
#include "Geometry.h"
#include "Mathematics.h"
#include "ogresource.h"

#define MAX_TERRAIN_PARTS   8


class COGTerrain : public IOGTerrain, public COGResource
{
public:
	COGTerrain ();
	virtual ~COGTerrain();

	// Load terrain.
	virtual bool Load ();

	// Set terrain position.
	virtual void SetWorldPosition (const Vec3& _vPos);

	// Render terrain.
	virtual void Render (const MATRIX& _mView);

	// Render.
	virtual void Render (const MATRIX& _mView, unsigned int _Part);

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_TERRAIN; }

    // Get ray intersection
    virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const {return m_pMesh->GetGeometry(); }

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;
	
private:

	IOGMesh*	    m_pMesh;	
	IOGTexture*	    m_pTexture[MAX_TERRAIN_PARTS];
    IOGMaterial*    m_pMaterial;
	Vec3		    m_vPosition;
};


#endif
