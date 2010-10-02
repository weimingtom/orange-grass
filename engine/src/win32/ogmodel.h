/*
 *  ogmodel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGMODEL_H_
#define OGMODEL_H_

#include "IOGModel.h"
#include "IOGMaterial.h"
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGAnimation.h"
#include "IOGSettingsReader.h"
#include <map>


class COGModel : public IOGModel, public COGResource
{
public:
	COGModel();
	virtual ~COGModel();
		
	// Load model.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// Update.
	virtual void Update (unsigned long _ElapsedTime);

	// Render mesh.
	virtual void Render (const MATRIX& _mWorld);

	// Render.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Part);

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_MODEL; }

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

	// Get model alias
	virtual const std::string& GetAlias () const;

	// Get texture
	virtual IOGTexture* GetTexture () { return m_pTexture; }

private:

	struct Cfg
	{
		std::string mesh_alias;
		std::string texture_alias;
		std::string material_type;
	};

	// Load model configuration
	bool LoadConfig (COGModel::Cfg& _cfg);

private:

	IOGMesh*	    m_pMesh;	
	IOGTexture*	    m_pTexture;
    IOGMaterial*    m_pMaterial;
    IOGRenderer*    m_pRenderer;
	IOGSettingsReader*	m_pReader;

	std::map<std::string, IOGAnimation*>	m_pAnimations;
};


#endif
