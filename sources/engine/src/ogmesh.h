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
#ifndef OGMESH_H_
#define OGMESH_H_

#include "IOGMath.h"
#include <vector>
#include <map>
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGRenderable.h"


class COGMesh : public IOGMesh
{
public:
    COGMesh ();
    virtual ~COGMesh();

    // Load mesh.
    virtual bool Load (
        OGMeshCfg* _pCfg,
        const char* _pName,
        SubMeshType _Type,
        unsigned int _Part,
        const void* _pVertexData, 
        unsigned int _NumVertices, 
        unsigned int _NumFaces,
        unsigned int _Stride, 
        const void* _pIndexData, 
        unsigned int _NumIndices);

    // Unload resource.
    virtual void Unload ();

    // Render mesh.
    virtual void Render (const OGMatrix& _mWorld, OGRenderPass _Pass);

    // Get type
    virtual SubMeshType GetType() const { return m_type; }

    // Get part
    virtual unsigned int GetPart() const { return m_part; }

    // Get name
    virtual const std::string& GetName() const { return m_name; }

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const { return *m_aabb; }

    // Get texture
    virtual IOGTexture* GetTexture () { return m_pTexture; }

    // Get material
    virtual IOGMaterial* GetMaterial () { return m_pMaterial; }

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos);

    // calculate geometry
    void CalculateGeometry (const OGMatrix& _initialMat);

protected:

    unsigned int        m_part;
    SubMeshType         m_type;
    std::string         m_name;
    IOGAabb*            m_aabb;
    IOGVertexBuffers*   m_buffer;
    std::vector<OGFace> m_faces;
    OGMeshCfg*          m_pCfg;
    IOGTexture*         m_pTexture;
    IOGMaterial*        m_pMaterial;

    IOGRenderer*    m_pRenderer;
};


#endif
