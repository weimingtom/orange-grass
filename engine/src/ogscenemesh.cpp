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


COGSceneMesh::COGSceneMesh () :	m_pScene (NULL)
{
    m_pRenderer = GetRenderer();
	m_pScene = new CPVRTModelPOD();
    m_NumParts = 0;
}


COGSceneMesh::~COGSceneMesh()
{
	Unload();
	OG_SAFE_DELETE(m_pScene);
}


// Load resource
bool COGSceneMesh::Load ()
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

	if (!m_pScene->ReadFromFile(m_ResourceFile.c_str()))
	{
        OG_LOG_ERROR("Failed to load mesh from file %s", m_ResourceFile.c_str());
		return false;
	}
	
    m_NumParts = 0;
    m_SubMeshes.reserve(m_pScene->nNumMeshNode);
	m_SolidParts.reserve(m_pScene->nNumMeshNode);
	m_TransparentParts.reserve(m_pScene->nNumMeshNode);
    for(unsigned int i = 0; i < m_pScene->nNumMeshNode; ++i)
    {
		SPODNode* pNode = &m_pScene->pNode[i];
		SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];

        SceneMesh submesh;
        submesh.type = GetSceneMeshType(i);
        submesh.part = i;
        submesh.buffer = m_pRenderer->CreateVertexBuffer(&Mesh);
        m_SubMeshes.push_back(submesh);
		switch (submesh.type)
		{
		case OG_SCENEMESH_TERRA: 
			m_TerraParts.push_back(m_NumParts); 
			break;
		case OG_SCENEMESH_SOLID_OBJ: 
			m_SolidParts.push_back(m_NumParts); 
			break;
		case OG_SCENEMESH_TRANSPARENT_OBJ: 
			m_TransparentParts.push_back(m_NumParts); 
			break;
		}
        ++m_NumParts;
    }

    CalculateGeometry();

    m_LoadState = OG_RESSTATE_LOADED;

    return true;
}


// Unload resource.
void COGSceneMesh::Unload ()
{
    if (m_LoadState != OG_RESSTATE_LOADED)
    {
        return;
    }

	OG_SAFE_DELETE(m_pScene);
    m_Faces.clear();
    m_AABB.SetMinMax(Vec3(0,0,0), Vec3(0,0,0));

    std::vector<SceneMesh>::iterator iter = m_SubMeshes.begin();
    for (; iter != m_SubMeshes.end(); ++iter)
    {
        OG_SAFE_DELETE((*iter).buffer);
        OG_SAFE_DELETE((*iter).aabb);
    }
    m_SubMeshes.clear();

	m_TerraParts.clear();
	m_SolidParts.clear();
	m_TransparentParts.clear();

	m_NumParts = 0;
	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render parts of the mesh.
void COGSceneMesh::RenderTerraParts (const MATRIX& _mWorld, const IOGFrustum& _frustum)
{
	MATRIX mNodeWorld, mModel;
	PartsList::const_iterator iter = m_TerraParts.begin();
	for (; iter != m_TerraParts.end(); ++iter)
	{
		unsigned int Id = *iter;
		SceneMesh& submesh = m_SubMeshes[Id];
		if (_frustum.CheckAabb(*submesh.aabb))
		{
			m_pScene->SetFrame(0);
			const SPODNode& node = m_pScene->pNode[submesh.part];

			// Gets the node model matrix
			m_pScene->GetWorldMatrix(mNodeWorld, node);

			// Multiply on the global world transform
			MatrixMultiply(mModel, mNodeWorld, _mWorld);

			m_pRenderer->SetModelMatrix(mModel);
			m_pRenderer->RenderMesh(submesh.buffer);
		}
	}
}


// Render parts of the mesh.
void COGSceneMesh::RenderSolidParts (const MATRIX& _mWorld, const IOGFrustum& _frustum)
{
	MATRIX mNodeWorld, mModel;
	PartsList::const_iterator iter = m_SolidParts.begin();
	for (; iter != m_SolidParts.end(); ++iter)
	{
		unsigned int Id = *iter;
		SceneMesh& submesh = m_SubMeshes[Id];
		if (_frustum.CheckAabb(*submesh.aabb))
		{
			m_pScene->SetFrame(0);
			const SPODNode& node = m_pScene->pNode[submesh.part];

			// Gets the node model matrix
			m_pScene->GetWorldMatrix(mNodeWorld, node);

			// Multiply on the global world transform
			MatrixMultiply(mModel, mNodeWorld, _mWorld);

			m_pRenderer->SetModelMatrix(mModel);
			m_pRenderer->RenderMesh(submesh.buffer);
		}
	}
}


// Render parts of the mesh.
void COGSceneMesh::RenderTransparentParts (const MATRIX& _mWorld, const IOGFrustum& _frustum)
{
	MATRIX mNodeWorld, mModel;
	PartsList::const_iterator iter = m_TransparentParts.begin();
	for (; iter != m_TransparentParts.end(); ++iter)
	{
		unsigned int Id = *iter;
		SceneMesh& submesh = m_SubMeshes[Id];
		if (_frustum.CheckAabb(*submesh.aabb))
		{
			m_pScene->SetFrame(0);
			const SPODNode& node = m_pScene->pNode[submesh.part];

			// Gets the node model matrix
			m_pScene->GetWorldMatrix(mNodeWorld, node);

			// Multiply on the global world transform
			MatrixMultiply(mModel, mNodeWorld, _mWorld);

			m_pRenderer->SetModelMatrix(mModel);
			m_pRenderer->RenderMesh(submesh.buffer);
		}
	}
}


// calculate geometry
void COGSceneMesh::CalculateGeometry ()
{
	MATRIX mModel;
    Vec3 v, vMinCorner, vMaxCorner;

    m_Faces.reserve(4096);
    unsigned int Part = 0;
    for (unsigned int i=0; i < m_pScene->nNumMeshNode; ++i)
	{
        SPODNode* pNode = &m_pScene->pNode[i];
		m_pScene->GetWorldMatrix(mModel, *pNode);

        SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];

        Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
		
		vMinCorner.x = vMaxCorner.x = pPtr->x; 
		vMinCorner.y = vMaxCorner.y = pPtr->y; 
		vMinCorner.z = vMaxCorner.z = pPtr->z;
		MatrixVecMultiply(vMinCorner, vMinCorner, mModel);
		MatrixVecMultiply(vMaxCorner, vMaxCorner, mModel);

		if(Mesh.sFaces.pData)
        {
			unsigned int numIndices = PVRTModelPODCountIndices(Mesh);
            for (unsigned int n = 0; n < numIndices; n+=3)
            {
                OGFace face;
                for (int k = 0; k < 3; ++k)
                {
                    unsigned short ind = *(((unsigned short*)Mesh.sFaces.pData) + n + k);
                    face.vertices[k] = *((Vec3*)((unsigned char*)(pPtr)+Mesh.sVertex.nStride * ind));

                    Vec3& v_out = face.vertices[k];
                    MatrixVecMultiply(v_out, face.vertices[k], mModel);

			        if (v_out.x < vMinCorner.x) vMinCorner.x = v_out.x;
			        if (v_out.y < vMinCorner.y) vMinCorner.y = v_out.y;
			        if (v_out.z < vMinCorner.z) vMinCorner.z = v_out.z;
			        if (v_out.x > vMaxCorner.x) vMaxCorner.x = v_out.x;
			        if (v_out.y > vMaxCorner.y) vMaxCorner.y = v_out.y;
			        if (v_out.z > vMaxCorner.z) vMaxCorner.z = v_out.z;
                }
                m_Faces.push_back(face);
            }
        }

        IOGAabb* pAabb = new IOGAabb(vMinCorner, vMaxCorner);
        m_SubMeshes[Part].aabb = pAabb;
		m_AABB.EmbraceAABB(*pAabb);
        ++Part;
	}
}


// Get combined AABB
const IOGAabb& COGSceneMesh::GetAABB () const
{
	return m_AABB;
}


// Get ray intersection
bool COGSceneMesh::GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos)
{
	float t, u, v;
	bool bIntersected = false;
    unsigned int numFaces = m_Faces.size();
	for (unsigned int i = 0; i < numFaces; ++i)
	{
        Vec3 p0 = m_Faces[i].vertices[0];
        Vec3 p1 = m_Faces[i].vertices[1];
        Vec3 p2 = m_Faces[i].vertices[2];
		bIntersected = CheckTriangleIntersection (_vRayPos, _vRayDir, p0, p1, p2, &t, &u, &v );
		if (bIntersected)
		{
			*_pOutPos = Barycentric2World(u, v, p0, p1, p2);
			return true;
		}
	}
	return false;
}


// get scene mesh type.
SceneMeshType COGSceneMesh::GetSceneMeshType (unsigned int _Id)
{
    SPODNode* pNode = &m_pScene->pNode[_Id];

	char propeller_prefix[] = "terra";
    if (strstr(pNode->pszName, propeller_prefix) == pNode->pszName)
    {
        return OG_SCENEMESH_TERRA;
    }

	char transparent_prefix[] = "alpha";
    if (strstr(pNode->pszName, transparent_prefix) == pNode->pszName)
    {
        return OG_SCENEMESH_TRANSPARENT_OBJ;
    }

	return OG_SCENEMESH_SOLID_OBJ;
}
