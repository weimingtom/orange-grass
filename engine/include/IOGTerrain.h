/*
 *  IOGTerrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGTERRAIN_H_
#define IOGTERRAIN_H_

#include "IOGRenderable.h"
#include "IOGTexture.h"


class IOGTerrain : public IOGRenderable
{
public:
	virtual ~IOGTerrain() {}
	
	// Save the terrain.
	virtual bool Save (const char* _pPath) = 0;
	
	// Set terrain position.
	virtual void SetWorldPosition (const Vec3& _vPos) = 0;

	// Set terrain texture.
	virtual void SetTexture (IOGTexture* _pTexture) = 0;

	// Modify the heights of the vertices in the heighmap grid
	virtual void AddHeight (const Vec3& _vPos, int _patchsize, float _v, bool _bSmoothen) = 0;

	// Modify the color of the vertices in the heighmap grid
	virtual void ChangeColor (const Vec3& _vPos, int _patchsize, const Vec3& _color) = 0;

	// Get the array of vertices that are within the area of the patch
	virtual int GetPatch (const Vec3& _vPos, int _patchsize, Vec3* _pOut) = 0;

	// Smoothen the vertices that are within the area of the patch
	virtual void SmoothenPatch (const Vec3& _vPos, int _patchsize) = 0;

	// Get ray intersection
	virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos) = 0;
};


#endif