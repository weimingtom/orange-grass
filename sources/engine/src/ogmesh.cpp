/*
 *  ogmesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogmesh.h"
#include "OrangeGrass.h"


COGMesh::COGMesh ()
{
    m_pRenderer = GetRenderer();
}


COGMesh::~COGMesh()
{
}


// load sub-meshes
void COGMesh::LoadSubMeshes ()
{
	m_SolidParts.reserve(m_pScene->nNumMeshNode);
	m_TransparentParts.reserve(m_pScene->nNumMeshNode);

    for(unsigned int i = 0; i < m_pScene->nNumMeshNode; ++i)
    {
		SPODNode* pNode = &m_pScene->pNode[i];
		SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];
        std::string subMeshName = std::string(pNode->pszName);

        SubMeshType sbmtype = ParseSubMeshType(subMeshName);
		switch (sbmtype)
		{
            case OG_SUBMESH_ACTPOINT:
            {
                OGVec3* pPtr = (OGVec3*)Mesh.pInterleaved;
                ActPoint pt;
                pt.pos = *pPtr;
                pt.part = i;
                m_ActivePoints[subMeshName] = pt;
                continue;
            }break;
                
            case OG_SUBMESH_BODY: m_SolidParts.push_back(m_NumParts); break;
            case OG_SUBMESH_PROPELLER: m_TransparentParts.push_back(m_NumParts); break;
		}

        OGSubMesh submesh;
        submesh.type = sbmtype;
        submesh.part = i;
        submesh.name = subMeshName;
        submesh.buffer = m_pRenderer->CreateVertexBuffer(&Mesh);
        m_SubMeshes.push_back(submesh);
        ++m_NumParts;
    }
}


// unload sub-meshes
void COGMesh::UnloadSubMeshes ()
{
	m_SolidParts.clear();
	m_TransparentParts.clear();
    m_ActivePoints.clear();
}


// Render mesh.
void COGMesh::Render (const OGMatrix& _mWorld, unsigned int _Frame)
{
    if (_Frame > m_pScene->nNumFrame)
        return;

	RenderSolidParts(_mWorld, _Frame);
}


// Render solid parts of the mesh.
void COGMesh::RenderSolidParts (const OGMatrix& _mWorld, unsigned int _Frame)
{
	std::vector<unsigned int>::const_iterator iter = m_SolidParts.begin();
	for (; iter != m_SolidParts.end(); ++iter)
	{
        RenderPart(_mWorld, *iter, _Frame);
	}
}


// Render transparent parts of the mesh.
void COGMesh::RenderTransparentParts (const OGMatrix& _mWorld, unsigned int _Frame, float _fSpin)
{
	OGMatrix mNodeWorld, mModel, mSpin;
	std::vector<unsigned int>::const_iterator iter = m_TransparentParts.begin();
	for (; iter != m_TransparentParts.end(); ++iter)
	{
		OGSubMesh& submesh = m_SubMeshes[*iter];
		m_pScene->SetFrame((float)_Frame);
		const SPODNode& node = m_pScene->pNode[submesh.part];

		MatrixRotationY(mSpin, _fSpin);

		// Gets the node model matrix
		m_pScene->GetWorldMatrix(mNodeWorld, node);
		MatrixMultiply(mNodeWorld, mSpin, mNodeWorld);

		// Multiply on the global world transform
		MatrixMultiply(mModel, mNodeWorld, _mWorld);

		m_pRenderer->SetModelMatrix(mModel);
		m_pRenderer->RenderMesh(submesh.buffer);
	}
}


// Render part of the mesh.
void COGMesh::RenderPart (const OGMatrix& _mWorld, unsigned int _Part, unsigned int _Frame)
{
    OGSubMesh& submesh = m_SubMeshes[_Part];
    m_pScene->SetFrame((float)_Frame);
    const SPODNode& node = m_pScene->pNode[submesh.part];

    // Gets the node model matrix
    OGMatrix mNodeWorld;
    m_pScene->GetWorldMatrix(mNodeWorld, node);

    // Multiply on the global world transform
    OGMatrix mModel;
    MatrixMultiply(mModel, mNodeWorld, _mWorld);

    m_pRenderer->SetModelMatrix(mModel);
    m_pRenderer->RenderMesh(submesh.buffer);
}


// Get num animation frames.
unsigned int COGMesh::GetNumFrames () const
{
    return m_pScene->nNumFrame;
}


// Check if has submeshes of the following type
bool COGMesh::HasSubmeshesOfType(SubMeshType _Type) const
{
	switch (_Type)
	{
	case OG_SUBMESH_BODY: 
		return !m_SolidParts.empty();

	case OG_SUBMESH_PROPELLER: 
		return !m_TransparentParts.empty();

	case OG_SUBMESH_ACTPOINT: 
		return !m_ActivePoints.empty();
	}
	return false;
}


// Get part AABB
const IOGAabb& COGMesh::GetPartAABB (unsigned int _Part) const 
{
    return *(m_SubMeshes[_Part].aabb);
}


// Get part's transformed OBB after applying animation
bool COGMesh::GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, const OGMatrix& _mWorld) const
{
	_obb.Create(GetPartAABB(_Part));

    const OGSubMesh& submesh = m_SubMeshes[_Part];
	m_pScene->SetFrame((float)_Frame);
	const SPODNode& node = m_pScene->pNode[submesh.part];
	OGMatrix mNodeWorld;
	m_pScene->GetWorldMatrix(mNodeWorld, node);
    OGMatrix mModel;
    MatrixMultiply(mModel, mNodeWorld, _mWorld);

	_obb.UpdateTransform(mModel);
	return true;
}


// Get active point
bool COGMesh::GetActivePoint (OGVec3& _Point, const std::string& _Alias, unsigned int _Frame)
{
    std::map<std::string, ActPoint>::iterator iter = m_ActivePoints.find(_Alias);
    if (iter != m_ActivePoints.end())
    {
	    m_pScene->SetFrame((float)_Frame);
        const SPODNode& node = m_pScene->pNode[iter->second.part];

        // Gets the node model matrix
        OGMatrix mNodeWorld;
        m_pScene->GetWorldMatrix(mNodeWorld, node);
        
        MatrixVecMultiply(_Point, iter->second.pos, mNodeWorld);
        return true;
    }
    return false;
}
