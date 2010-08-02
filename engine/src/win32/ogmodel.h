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


class COGModel : public IOGModel, public COGResource
{
public:
	COGModel();
	virtual ~COGModel();
		
	// Load model.
	virtual bool Load ();
		
	// Update mesh animation.
	virtual void UpdateAnimation (int _ElapsedTime);

	// Render mesh.
	virtual void Render (const MATRIX& _mView);

	// Render.
	virtual void Render (const MATRIX& _mView, unsigned int _Part);

    // Get num renderable parts.
	virtual unsigned int GetNumRenderables () const;

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_MODEL; }

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

public:

	IOGMesh*	    m_pMesh;	
	IOGTexture*	    m_pTexture;
    IOGMaterial*    m_pMaterial;
};


#endif
