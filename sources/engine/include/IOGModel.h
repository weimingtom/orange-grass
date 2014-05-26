/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
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
