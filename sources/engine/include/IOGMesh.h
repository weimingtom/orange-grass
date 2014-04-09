/*
 *  IOGModel.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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