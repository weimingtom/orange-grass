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
#include <list>
#include "ogmodelconfig.h"
#include "ogmodelskeleton.h"


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
    virtual void Render (const OGMatrix& _mWorld, unsigned int _MeshId, OGRenderPass _Pass);

    // Get type of the renderable.
    virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_MODEL; }

    // Get combined AABB
    virtual const IOGAabb& GetAABB () const { return m_AABB; }

    // Get model alias
    virtual const std::string& GetAlias () const { return m_ResourceAlias; }

    // Get model skeleton
    virtual IOGModelSkeleton* GetModelSkeleton () { return &m_Skeleton; }

    // Get animation
    virtual IOGAnimation* GetAnimation (const std::string& _Alias);

    // Get mesh
    virtual const std::vector<IOGMesh*>& GetMeshes () const { return m_Meshes; }

    // Save params
    virtual bool SaveParams ();

    // Get ray intersection
    virtual bool GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos);

private:

    IOGAabb                         m_AABB;
    IOGRenderer*                    m_pRenderer;
    COGModelConfig                  m_Cfg;
    COGModelSkeleton                m_Skeleton;
    std::vector<IOGMesh*>           m_Meshes;
    std::vector<IOGActivePoint*>    m_ActivePoints;
};

#endif
