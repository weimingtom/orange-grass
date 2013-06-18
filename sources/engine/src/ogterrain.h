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

#include "IOGTerrain.h"
#include "IOGMaterial.h"
#include "IOGMath.h"
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"
#include "ogscenemesh.h"


class COGTerrain : public IOGTerrain, public COGResource
{
public:
	COGTerrain ();
	virtual ~COGTerrain();

	// Load terrain.
	virtual bool Load ();

	// Unload terrain.
	virtual void Unload ();

	// Render terrain.
	virtual void Render (const OGMatrix& _mWorld);

	// Render all.
	virtual void RenderAll (const OGMatrix& _mWorld);

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_TERRAIN; }

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos);

    // Get mesh geometry
    virtual const std::vector<OGFace>& GetGeometry () const {return m_pMesh->GetGeometry(); }

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

	// Get all submesh AABBs
    virtual void GetAllAABBs (std::vector<IOGAabb*>& _aabbs);

	// Get material
	//virtual IOGMaterial* GetMaterial () { return m_pMaterial; }

	// Save params
	virtual bool SaveParams ();

private:

	struct Cfg
	{
        OGVec4 material_ambient;
        OGVec4 material_diffuse;
        OGVec4 material_specular;
		std::string mesh_file;
		std::string texture_alias;
		OGBlendType blend_type;
	};

	// Load terrain configuration
	bool LoadConfig (COGTerrain::Cfg& _cfg);
	
private:

	COGSceneMesh*				m_pMesh;	
    IOGMaterial*				m_pMaterial;
	IOGTexture*					m_pTexture;
	OGBlendType					m_Blend;
    IOGRenderer*                m_pRenderer;
	IOGSettingsReader*			m_pReader;
	IOGGlobalVarsTable*			m_pGlobalVars;
};


#endif
