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
    : m_pTexture(NULL)
    , m_pMaterial(NULL)
    , m_NumParts(0)
{
    m_pRenderer = GetRenderer();
    m_pReader = GetSettingsReader();
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
    if (!pScene->ReadFromFile(m_Cfg.GetMeshConfig()->mesh_file.c_str()))
    {
        OG_LOG_ERROR("Failed to load mesh from file %s", m_Cfg.GetMeshConfig()->mesh_file.c_str());
        return false;
    }
    pScene->SetFrame(0);

    m_NumParts = 0;
    m_Meshes.reserve(pScene->nNumMeshNode);
    m_SolidParts.reserve(pScene->nNumMeshNode);
    m_TransparentParts.reserve(pScene->nNumMeshNode);
    m_AnimationSet.SetNumFrames(pScene->nNumFrame);

    for(unsigned int i = 0; i < pScene->nNumNode; ++i)
    {
        SPODNode* pNode = &pScene->pNode[i];

        AnimationNode* pAnimNode = m_AnimationSet.AddNode(pNode->nIdx, pNode->nIdxParent, pNode->pfAnimMatrix);

        if (pNode->nIdx >= 0)
        {
            SPODMesh& Mesh = pScene->pMesh[pNode->nIdx];

            std::string subMeshName = std::string(pNode->pszName);
            SubMeshType sbmtype = ParseSubMeshType(subMeshName);
            switch (sbmtype)
            {
            case OG_SUBMESH_ACTPOINT:
                {
                    OGVec3* pPtr = (OGVec3*)Mesh.pInterleaved;
                    IOGActivePoint pt;
                    pt.pos = *pPtr;
                    pt.part = i;
                    m_ActivePoints[subMeshName] = pt;
                    pAnimNode->pBody = &m_ActivePoints[subMeshName];
                    pAnimNode->BodyType = OG_SUBMESH_ACTPOINT;
                    continue;
                }
                break;

            case OG_SUBMESH_BODY:
                m_SolidParts.push_back(m_NumParts); 
                pAnimNode->BodyType = OG_SUBMESH_BODY;
                break;

            case OG_SUBMESH_PROPELLER:
                m_TransparentParts.push_back(m_NumParts);
                pAnimNode->BodyType = OG_SUBMESH_PROPELLER;
                break;
            }

            COGMesh* pMesh = new COGMesh();
            if (!pMesh->Load(subMeshName.c_str(), sbmtype, /*i*/pNode->nIdx, Mesh.pInterleaved, Mesh.nNumVertex, 
                Mesh.nNumFaces, Mesh.sVertex.nStride, Mesh.sFaces.pData, PVRTModelPODCountIndices(Mesh)))
            {
                OG_LOG_ERROR("Failed to load model's mesh %s", m_Cfg.GetMeshConfig()->mesh_file.c_str());
                OG_SAFE_DELETE(pMesh);
                return false;
            }

            pAnimNode->pBody = pMesh;

            OGMatrix mModel;
            pScene->GetWorldMatrix(mModel, *pNode);
            pMesh->CalculateGeometry(mModel);
            m_AABB.EmbraceAABB(pMesh->GetAABB());
            m_Meshes.push_back(pMesh);

            ++m_NumParts;
        }
        else
        {
            pAnimNode->BodyType = OG_SUBMESH_DUMMY;
            pAnimNode->pBody = NULL;
        }
    }

    delete pScene;

    AnimationNode* pRootNode = m_AnimationSet.BuildSG();

    m_pTexture = GetResourceMgr()->GetTexture(OG_RESPOOL_GAME, m_Cfg.GetMaterialConfig()->texture_alias.c_str());
    m_pMaterial = m_pRenderer->CreateMaterial();
    m_pMaterial->LoadConfig(m_Cfg.GetMaterialConfig());

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

    m_SolidParts.clear();
    m_TransparentParts.clear();
    m_ActivePoints.clear();

    OG_SAFE_DELETE(m_pMaterial);

    std::for_each(m_Meshes.begin(), m_Meshes.end(), [](IOGMesh* m) { m->Unload(); OG_SAFE_DELETE(m); });
    m_Meshes.clear();

    m_AnimationSet.Clear();

    m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGModel::Render (const OGMatrix& _mWorld, unsigned int _Frame, float _fBlend, float _fSpin)
{
    std::for_each(m_Meshes.begin(), m_Meshes.end(), [&](IOGMesh* m) 
    {
        OGBlendType blend = m_pMaterial->GetBlend();
        OGMatrix mNodeWorld, mModel;
        m_AnimationSet.GetWorldMatrix(mNodeWorld, m->GetPart(), _Frame, _fBlend);
        if (std::find(m_TransparentParts.begin(), m_TransparentParts.end(), m->GetPart()) != m_TransparentParts.end())
        {
            OGMatrix mSpin;
            MatrixRotationY(mSpin, _fSpin);
            MatrixMultiply(mNodeWorld, mSpin, mNodeWorld);
            blend = OG_BLEND_ALPHABLEND;
        }
        MatrixMultiply(mModel, mNodeWorld, _mWorld);
        m_pRenderer->Render(m_pTexture, m_pMaterial, m->GetVertexBuffer(), mModel, blend, OG_SHADER_MODEL);
    });
}


// Check if has submeshes of the following type
bool COGModel::HasSubmeshesOfType(SubMeshType _Type) const
{
    bool bResult = false;
    std::for_each(m_Meshes.begin(), m_Meshes.end(), [&](IOGMesh* m)
    { 
        if (m->GetType() == _Type)
            bResult = true;
    });
    return bResult;
}


// Get num renderable parts.
unsigned int COGModel::GetNumRenderables () const
{
    return (unsigned int)m_Meshes.size();
}


// Get part's transformed OBB after applying animation
bool COGModel::GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, float _fBlend, const OGMatrix& _mWorld)
{
    const IOGMesh* pMesh = m_Meshes[_Part];
    OGMatrix mNodeWorld, mModel;
    m_AnimationSet.GetWorldMatrix(mNodeWorld, pMesh->GetPart(), _Frame, _fBlend);
    MatrixMultiply(mModel, mNodeWorld, _mWorld);
    _obb.Create(pMesh->GetAABB());
    _obb.UpdateTransform(mModel);
    return true;
}


// Get animation
IOGAnimation* COGModel::GetAnimation (const std::string& _Alias)
{
    return &m_Cfg.GetAnimationConfig()->anim_list[_Alias];
}


// Get active point
bool COGModel::GetActivePoint (IOGActivePoint& _point, const std::string& _Alias, unsigned int _Frame, float _fBlend)
{
    auto iter = m_ActivePoints.find(_Alias);
    if (iter != m_ActivePoints.end())
    {
        OGMatrix mNodeWorld;
        m_AnimationSet.GetWorldMatrix(mNodeWorld, iter->second.part, _Frame, _fBlend);
        MatrixVecMultiply(_point.pos, iter->second.pos, mNodeWorld);
        _point.alias = _Alias;
        return true;
    }

    return false;
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
