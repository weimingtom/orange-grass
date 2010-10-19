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
#include "Geometry.h"
#include "Mathematics.h"
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"


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
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame);
		
	// Update mesh animation.
	virtual void Update (unsigned long _ElapsedTime);

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

	// Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) {return NULL;}

private:

	struct Cfg
	{
		struct TextureCfg
		{
			std::string alias;
		};

		std::string mesh_alias;
		std::vector<TextureCfg> texture_cfg_list;
	};

	// Load terrain configuration
	bool LoadConfig (COGTerrain::Cfg& _cfg);
	
private:

	IOGMesh*					m_pMesh;	
	std::vector<IOGTexture*>	m_TextureList;
    IOGMaterial*				m_pMaterial;
    IOGRenderer*                m_pRenderer;
	IOGSettingsReader*			m_pReader;
	IOGGlobalVarsTable*			m_pGlobalVars;
	float						m_fViewDistance;
};


#endif
