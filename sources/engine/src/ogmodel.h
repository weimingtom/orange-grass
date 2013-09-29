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
#include "ogresource.h"
#include "IOGRenderer.h"
#include "IOGSettingsReader.h"
#include "ogmesh.h"
#include <map>
#include <list>
#include "ogmodelconfig.h"
#include "oganimationset.h"


class COGModel : public IOGModel, public COGResource
{
public:
    COGModel();
    virtual ~COGModel();

    // Load model.
    virtual bool Load ();

    // Unload resource.
    virtual void Unload ();

    // Render mesh.
    virtual void Render (const OGMatrix& _mWorld, unsigned int _Frame, float _fBlend);

    // Render solid parts of the mesh.
    virtual void RenderSolidParts (const OGMatrix& _mWorld, unsigned int _Frame, float _fBlend);

    // Render transparent parts of the mesh.
    virtual void RenderTransparentParts (const OGMatrix& _mWorld, unsigned int _Frame, float _fBlend, float _fSpin);

    // Check if has submeshes of the following type
    virtual bool HasSubmeshesOfType(SubMeshType _Type) const;

    // Get num renderable parts.
    virtual unsigned int GetNumRenderables () const;

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_MODEL; }

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const { return m_AABB; }

    // Get part's transformed OBB after applying animation
    virtual bool GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, float _fBlend, const OGMatrix& _mWorld);

    // Get model alias
    virtual const std::string& GetAlias () const { return m_ResourceAlias; }

    // Get texture
    virtual IOGTexture* GetTexture () { return m_pTexture; }

    // Get material
    virtual IOGMaterial* GetMaterial () { return m_pMaterial; }

    // Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias);

    // Get mesh
    virtual const std::vector<IOGMesh*>& GetMeshes () const { return m_Meshes; }

    // Get active point
    virtual bool GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame, float _fBlend);

    // Save params
    virtual bool SaveParams ();

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos);

private:

    IOGTexture*         m_pTexture;
    IOGMaterial*        m_pMaterial;

    IOGAabb             m_AABB;
    unsigned int        m_NumParts;

    IOGRenderer*        m_pRenderer;
    IOGSettingsReader*  m_pReader;

    COGModelConfig      m_Cfg;
    COGAnimationSet     m_AnimationSet;

    std::vector<IOGMesh*>                   m_Meshes;
    std::vector<unsigned int>               m_SolidParts;
    std::vector<unsigned int>               m_TransparentParts;
    std::map<std::string, IOGActivePoint>   m_ActivePoints;
};

#endif
