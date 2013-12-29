/*
*  ogmodel.cpp
*  OrangeGrass
*
*  Created by Viacheslav Bogdanov on 08.11.09.
*  Copyright 2009 __MyCompanyName__. All rights reserved.
*
*/

#include "OrangeGrass.h"
#include "ogmodel.h"
#include "pvr/POD.h"


COGModel::COGModel() 
{
    m_pRenderer = GetRenderer();
}


COGModel::~COGModel()
{
    Unload();
}


// Load model.
bool COGModel::Load ()
{
    switch (m_LoadState)
    {
    case OG_RESSTATE_UNKNOWN:
        return false;

    case OG_RESSTATE_LOADED:
        return true;

    case OG_RESSTATE_DEFINED:
        break;
    }

    m_Cfg.LoadConfig(m_ResourceFile);

    CPVRTModelPOD* pScene = new CPVRTModelPOD();
    if (!pScene->ReadFromFile(m_Cfg.GetModelConfig()->model_file.c_str()))
    {
        OG_LOG_ERROR("Failed to load mesh from file %s", m_Cfg.GetModelConfig()->model_file.c_str());
        return false;
    }
    pScene->SetFrame(0);

    m_Meshes.reserve(pScene->nNumMeshNode);
    m_Skeleton.SetNumFrames(pScene->nNumFrame);
    unsigned int numMeshes = 0;

    for(unsigned int i = 0; i < pScene->nNumNode; ++i)
    {
        SPODNode* pNode = &pScene->pNode[i];

        OGModelNode* pAnimNode = m_Skeleton.AddNode(pNode->nIdx, pNode->nIdxParent, pNode->pfAnimMatrix);

        if (pNode->nIdx >= 0)
        {
            SPODMesh& Mesh = pScene->pMesh[pNode->nIdx];

            std::string subMeshName = std::string(pNode->pszName);
            SubMeshType sbmtype = ParseSubMeshType(subMeshName);
            pAnimNode->BodyType = sbmtype;
            switch (sbmtype)
            {
            case OG_SUBMESH_DUMMY:
                break;

            case OG_SUBMESH_ACTPOINT:
                {
                    OGVec3* pPtr = (OGVec3*)Mesh.pInterleaved;
                    IOGActivePoint* pt = new IOGActivePoint();
                    pt->alias = subMeshName;
                    pt->pos = *pPtr;
                    pt->part = i;
                    m_ActivePoints.push_back(pt);
                    pAnimNode->pBody = pt;
                    pAnimNode->BodyType = OG_SUBMESH_ACTPOINT;
                }
                break;

            default:
                {
                    COGMesh* pMesh = new COGMesh();
                    OGMeshCfg* pMeshCfg = &m_Cfg.GetModelConfig()->mesh_cfg[numMeshes];
                    if (!pMesh->Load(pMeshCfg, subMeshName.c_str(), sbmtype, i, Mesh.pInterleaved, Mesh.nNumVertex, 
                        Mesh.nNumFaces, Mesh.sVertex.nStride, Mesh.sFaces.pData, PVRTModelPODCountIndices(Mesh)))
                    {
                        OG_LOG_ERROR("Failed to load model's mesh %s", m_Cfg.GetModelConfig()->model_file.c_str());
                        OG_SAFE_DELETE(pMesh);
                        return false;
                    }

                    pAnimNode->pBody = pMesh;
                    pAnimNode->SceneProps = pMeshCfg->sceneprops;

                    OGMatrix mModel;
                    pScene->GetWorldMatrix(mModel, *pNode);
                    pMesh->CalculateGeometry(mModel);
                    m_AABB.EmbraceAABB(pMesh->GetAABB());
                    m_Meshes.push_back(pMesh);
                    ++numMeshes;
                }
                break;
            }
        }
        else
        {
            pAnimNode->BodyType = OG_SUBMESH_DUMMY;
            pAnimNode->pBody = NULL;
        }
    }

    OG_SAFE_DELETE(pScene);

    OGModelNode* pRootNode = m_Skeleton.BuildSG();

    m_LoadState = OG_RESSTATE_LOADED;
    return true;
}


// Save params
bool COGModel::SaveParams ()
{
    return m_Cfg.SaveConfig();
}


// Unload resource.
void COGModel::Unload ()
{
    if (m_LoadState != OG_RESSTATE_LOADED)
    {
        return;
    }
    for (auto it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
    {
        (*it)->Unload(); OG_SAFE_DELETE((*it));
    }
    m_Meshes.clear();
    for( auto it = m_ActivePoints.begin(); it != m_ActivePoints.end(); ++it)
    {
        OG_SAFE_DELETE(*it);
    }
    m_ActivePoints.clear();

    m_Skeleton.Clear();

    m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGModel::Render (const OGMatrix& _mWorld, unsigned int _MeshId, OGRenderPass _Pass)
{
    m_Meshes[_MeshId]->Render(_mWorld, _Pass);
}


// Get animation
IOGAnimation* COGModel::GetAnimation (const std::string& _Alias)
{
    return &m_Cfg.GetAnimationConfig()->anim_list[_Alias];
}


// Get ray intersection
bool COGModel::GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos)
{
    for (auto it = m_Meshes.begin(); it != m_Meshes.end(); ++it)
    {
        if ((*it)->GetRayIntersection(_vRayPos, _vRayDir, _pOutPos))
            return true;
    }
    return false;
}
