/*
 *  IOGModel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGMODEL_H_
#define IOGMODEL_H_

#include "IOGRenderable.h"
#include "IOGTexture.h"
#include "IOGMesh.h"


class IOGModel
{
public:
	virtual ~IOGModel() {}

	// Get model alias
	virtual const std::string& GetAlias () const = 0;

	// Get texture
	virtual IOGTexture* GetTexture () = 0;

	// Render mesh.
	virtual void Render (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Render solid parts of the mesh.
	virtual void RenderSolidParts (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Render transparent parts of the mesh.
	virtual void RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame) = 0;

	// Check if has submeshes of the following type
	virtual bool HasSubmeshesOfType(SubMeshType _Type) const = 0;

	// Get combined AABB
	virtual const IOGAabb& GetAABB () const = 0;

	// Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) = 0;

	// Get active point
    virtual bool GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame) = 0;
};


#endif
