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
#include "IOGMaterial.h"
#include "IOGMesh.h"
#include "IOGMath.h"
#include "IOGObb.h"
#include <vector>


class IOGModel
{
public:
    virtual ~IOGModel() {}

    // Get model alias
    virtual const std::string& GetAlias () const = 0;

    // Save params
    virtual bool SaveParams () = 0;

    // Get texture
    virtual IOGTexture* GetTexture () = 0;

    // Get material
    virtual IOGMaterial* GetMaterial () = 0;

    // Get mesh
    virtual const std::vector<IOGMesh*>& GetMeshes () const = 0;

    // Render mesh.
    virtual void Render (const OGMatrix& _mWorld, unsigned int _Frame) = 0;

    // Render solid parts of the mesh.
    virtual void RenderSolidParts (const OGMatrix& _mWorld, unsigned int _Frame) = 0;

    // Render transparent parts of the mesh.
    virtual void RenderTransparentParts (const OGMatrix& _mWorld, unsigned int _Frame, float _fSpin) = 0;

    // Check if has submeshes of the following type
    virtual bool HasSubmeshesOfType(SubMeshType _Type) const = 0;

    // Get num renderable parts.
    virtual unsigned int GetNumRenderables () const = 0;

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const = 0;

    // Get part's transformed OBB after applying animation
    virtual bool GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, const OGMatrix& _mWorld) const = 0;

    // Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) = 0;

    // Get active point
    virtual bool GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame) = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos) = 0;
};


#endif
