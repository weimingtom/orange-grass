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

        SubMeshType sbmtype = GetSubMeshType(i);
        if (sbmtype == OG_SUBMESH_ACTPOINT)
        {
            Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
            ActPoint pt;
            pt.pos = *pPtr;
            pt.part = i;
            m_ActivePoints[std::string(pNode->pszName)] = pt;
            continue;
        }

        SubMesh submesh;
        submesh.type = sbmtype;
        submesh.part = i;
        submesh.buffer = m_pRenderer->CreateVertexBuffer(&Mesh);
        m_SubMeshes.push_back(submesh);

		switch (submesh.type)
		{
		case OG_SUBMESH_BODY: m_SolidParts.push_back(m_NumParts); break;
		case OG_SUBMESH_PROPELLER: m_TransparentParts.push_back(m_NumParts); break;
		}
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
void COGMesh::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
    if (_Frame > m_pScene->nNumFrame)
        return;

	RenderSolidParts(_mWorld, _Frame);
}


// Render solid parts of the mesh.
void COGMesh::RenderSolidParts (const MATRIX& _mWorld, unsigned int _Frame)
{
	std::vector<unsigned int>::const_iterator iter = m_SolidParts.begin();
	for (; iter != m_SolidParts.end(); ++iter)
	{
        RenderPart(_mWorld, *iter, _Frame);
	}
}


// Render transparent parts of the mesh.
void COGMesh::RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame, float _fSpin)
{
	MATRIX mNodeWorld, mModel, mSpin;
	std::vector<unsigned int>::const_iterator iter = m_TransparentParts.begin();
	for (; iter != m_TransparentParts.end(); ++iter)
	{
		SubMesh& submesh = m_SubMeshes[*iter];
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
void COGMesh::RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame)
{
    SubMesh& submesh = m_SubMeshes[_Part];
    m_pScene->SetFrame((float)_Frame);
    const SPODNode& node = m_pScene->pNode[submesh.part];

    // Gets the node model matrix
    MATRIX mNodeWorld;
    m_pScene->GetWorldMatrix(mNodeWorld, node);

    // Multiply on the global world transform
    MATRIX mModel;
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
bool COGMesh::GetTransformedOBB (IOGObb& _obb, unsigned int _Part, unsigned int _Frame, const MATRIX& _mWorld) const
{
	_obb.Create(GetPartAABB(_Part));

    const SubMesh& submesh = m_SubMeshes[_Part];
	m_pScene->SetFrame((float)_Frame);
	const SPODNode& node = m_pScene->pNode[submesh.part];
	MATRIX mNodeWorld;
	m_pScene->GetWorldMatrix(mNodeWorld, node);
    MATRIX mModel;
    MatrixMultiply(mModel, mNodeWorld, _mWorld);

	_obb.UpdateTransform(mModel);
	return true;
}


// Get active point
bool COGMesh::GetActivePoint (Vec3& _Point, const std::string& _Alias, unsigned int _Frame)
{
    std::map<std::string, ActPoint>::iterator iter = m_ActivePoints.find(_Alias);
    if (iter != m_ActivePoints.end())
    {
	    m_pScene->SetFrame((float)_Frame);
        const SPODNode& node = m_pScene->pNode[iter->second.part];

        // Gets the node model matrix
        MATRIX mNodeWorld;
        m_pScene->GetWorldMatrix(mNodeWorld, node);
        
        MatrixVecMultiply(_Point, iter->second.pos, mNodeWorld);
        return true;
    }
    return false;
}
