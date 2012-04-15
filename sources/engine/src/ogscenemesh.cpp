/*
 *  ogscenemesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogscenemesh.h"
#include "OrangeGrass.h"


COGSceneMesh::COGSceneMesh ()
{
    m_pRenderer = GetRenderer();
}


COGSceneMesh::~COGSceneMesh()
{
}


// load sub-meshes
void COGSceneMesh::LoadSubMeshes ()
{
	m_TerraParts.reserve(m_pScene->nNumMeshNode);
    for(unsigned int i = 0; i < m_pScene->nNumMeshNode; ++i)
    {
		SPODNode* pNode = &m_pScene->pNode[i];
		SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];

        SubMesh submesh;
        submesh.type = GetSubMeshType(i);
        submesh.part = i;
        submesh.buffer = m_pRenderer->CreateVertexBuffer(&Mesh);
        m_SubMeshes.push_back(submesh);
		m_TerraParts.push_back(m_NumParts); 
        ++m_NumParts;
    }
}


// unload sub-meshes
void COGSceneMesh::UnloadSubMeshes ()
{
	m_TerraParts.clear();
}


// Render parts of the mesh.
void COGSceneMesh::RenderParts (const IOGFrustum& _frustum)
{
	OGMatrix mNodeWorld;
	PartsList::const_iterator iter = m_TerraParts.begin();
	for (; iter != m_TerraParts.end(); ++iter)
	{
		unsigned int Id = *iter;
		SubMesh& submesh = m_SubMeshes[Id];
        
		m_pScene->SetFrame(0);
		const SPODNode& node = m_pScene->pNode[submesh.part];

		// Gets the node model matrix
		m_pScene->GetWorldMatrix(mNodeWorld, node);

		//if (_frustum.CheckAabb(*submesh.aabb))
		{
			m_pRenderer->SetModelMatrix(mNodeWorld);
			m_pRenderer->RenderMesh(submesh.buffer);
		}
	}
}
