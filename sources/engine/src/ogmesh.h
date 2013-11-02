/*
 *  ogmesh.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
    virtual void Render (const OGMatrix& _mWorld);

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
