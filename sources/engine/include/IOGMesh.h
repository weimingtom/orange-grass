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
#ifndef IOGMESH_H_
#define IOGMESH_H_

#include "IOGGeometry.h"
#include "IOGVertexBuffers.h"
#include "IOGMaterial.h"
#include "IOGShader.h"
#include <vector>


struct OGMeshCfg
{
    OGShaderID      shaderID;
    OGShaderID      shadowShaderID;
    OGMaterialCfg   material_cfg;
    unsigned int    sceneprops;
};


class IOGMesh
{
public:
    virtual ~IOGMesh() {}

    // Unload resource.
    virtual void Unload () = 0;

    // Render mesh.
    virtual void Render (const OGMatrix& _mWorld, OGRenderPass _Pass) = 0;

    // Get type
    virtual SubMeshType GetType() const = 0;

    // Get part
    virtual unsigned int GetPart() const = 0;

    // Get name
    virtual const std::string& GetName() const = 0;

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const = 0;

    // Get texture
    virtual IOGTexture* GetTexture () = 0;

    // Get material
    virtual IOGMaterial* GetMaterial () = 0;

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos) = 0;
};

#endif