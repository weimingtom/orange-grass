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

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_MODEL; }

	// Get number of parts
	virtual int GetNumParts () const;

	// Get AABB for the specified part
	virtual const IOGAabb& GetAABB ( int _part ) const;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const;

public:

	IOGMesh*	    m_pMesh;	
	IOGTexture*	    m_pTexture;
    IOGMaterial*    m_pMaterial;
};


#endif
