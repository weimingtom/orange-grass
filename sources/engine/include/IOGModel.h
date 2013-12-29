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
#include "IOGModelSkeleton.h"
#include <vector>


struct OGModelCfg
{
    std::string             model_file;
    std::vector<OGMeshCfg>  mesh_cfg;
};


class IOGModel
{
public:
    virtual ~IOGModel() {}

    // Get model alias
    virtual const std::string& GetAlias () const = 0;

    // Save params
    virtual bool SaveParams () = 0;

    // Get model skeleton
    virtual IOGModelSkeleton* GetModelSkeleton () = 0;

    // Get mesh
    virtual const std::vector<IOGMesh*>& GetMeshes () const = 0;

    // Render mesh.
    virtual void Render (const OGMatrix& _mWorld, unsigned int _MeshId, OGRenderPass _Pass) = 0;

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const = 0;

    // Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias) = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos) = 0;
};


#endif
