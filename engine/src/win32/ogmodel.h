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

	// Render mesh.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame);

	// Render solid parts of the mesh.
	virtual void RenderSolidParts (const MATRIX& _mWorld, unsigned int _Frame);

	// Render transparent parts of the mesh.
	virtual void RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame, float _fSpin);

	// Check if has submeshes of the following type
	virtual bool HasSubmeshesOfType(SubMeshType _Type) const;

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

	// Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias);

	// Get active point
    virtual bool GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame);

private:

	struct Cfg
	{
		struct Anim
		{
			std::string anim_alias;
			int anim_start;
			int anim_end;
            int speed;
            int looped;
		};

		std::string mesh_alias;
		std::string texture_alias;
		std::string blend_type;
		std::list<Anim> anim_list;
	};

	// Load model configuration
	bool LoadConfig (COGModel::Cfg& _cfg);

private:

	IOGMesh*	    m_pMesh;	
	IOGTexture*	    m_pTexture;
	OGBlendType		m_Blend;
    IOGMaterial*    m_pMaterial;

	IOGRenderer*		m_pRenderer;
	IOGSettingsReader*	m_pReader;

	std::map<std::string, IOGAnimation*>	m_pAnimations;
};


#endif
