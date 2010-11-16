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


COGMesh::COGMesh () :	m_pScene (NULL)
{
    m_pRenderer = GetRenderer();
	m_pScene = (CPVRTModelPOD*)malloc(sizeof(CPVRTModelPOD));
	memset(m_pScene, 0, sizeof(CPVRTModelPOD));
    m_NumParts = 0;
}


COGMesh::~COGMesh()
{
	Unload();

	if (m_pScene)
	{
		free(m_pScene);
		m_pScene = NULL;
	}
}


// Load resource
bool COGMesh::Load ()
{	
	switch (m_LoadState)
	{
	case OG_RESSTATE_UNKNOWN:
		return false;

	case OG_RESSTATE_LOADED:
        return true;    
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
        if (IsActivePoint(i))
        {
            SPODNode* pNode = &m_pScene->pNode[i];
            SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];
            Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
            ActPoint pt;
            pt.pos = *pPtr;
            pt.part = i;
            m_ActivePoints[std::string(pNode->pszName)] = pt;
            continue;
        }

        SubMesh submesh;
        submesh.type = GetSubMeshType(i);
        submesh.part = i;
        submesh.buffer = m_pRenderer->CreateVertexBuffer(&m_pScene->pMesh[i]);
        m_SubMeshes.push_back(submesh);
		switch (submesh.type)
		{
		case OG_SUBMESH_BODY: m_SolidParts.push_back(m_NumParts); break;
		case OG_SUBMESH_PROPELLER: m_TransparentParts.push_back(m_NumParts); break;
		}
        ++m_NumParts;
    }

    CalculateGeometry();

    m_LoadState = OG_RESSTATE_LOADED;

    return true;
}


// Unload resource.
void COGMesh::Unload ()
{
    if (m_LoadState != OG_RESSTATE_LOADED)
    {
        return;
    }

    memset(m_pScene, 0, sizeof(CPVRTModelPOD));
    m_Faces.clear();
    m_AABB.SetMinMax(Vec3(0,0,0), Vec3(0,0,0));

    std::vector<SubMesh>::iterator iter = m_SubMeshes.begin();
    for (; iter != m_SubMeshes.end(); ++iter)
    {
        OG_SAFE_DELETE((*iter).buffer);
        OG_SAFE_DELETE((*iter).aabb);
    }
    m_SubMeshes.clear();
	m_SolidParts.clear();
	m_TransparentParts.clear();

    m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGMesh::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
    if (_Frame > m_pScene->nNumFrame)
        return;

	RenderSolidParts(_mWorld, _Frame);
    //for (unsigned int i = 0; i < m_NumParts; ++i)
    //{
    //    RenderPart(_mWorld, i, _Frame);
    //}
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
void COGMesh::RenderTransparentParts (const MATRIX& _mWorld, unsigned int _Frame)
{
	std::vector<unsigned int>::const_iterator iter = m_TransparentParts.begin();
	for (; iter != m_TransparentParts.end(); ++iter)
	{
        RenderPart(_mWorld, *iter, _Frame);
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


// Get num renderable parts.
unsigned int COGMesh::GetNumRenderables () const
{
    return m_NumParts;
}


// Get num animation frames.
unsigned int COGMesh::GetNumFrames () const
{
    return m_pScene->nNumFrame;
}


// calculate geometry
void COGMesh::CalculateGeometry ()
{
	MATRIX mModel;
    Vec3 v, vMinCorner, vMaxCorner;

    m_Faces.reserve(4096);
    unsigned int Part = 0;
    for (unsigned int i=0; i < m_pScene->nNumMeshNode; ++i)
	{
        if (IsActivePoint(i))
        {
            continue;
        }

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


// Check if has submeshes of the following type
bool COGMesh::HasSubmeshesOfType(SubMeshType _Type) const
{
	switch (_Type)
	{
	case OG_SUBMESH_BODY: 
		return !m_SolidParts.empty();

	case OG_SUBMESH_PROPELLER: 
		return !m_TransparentParts.empty();
	}
	return false;
}


// Get combined AABB
const IOGAabb& COGMesh::GetAABB () const
{
	return m_AABB;
}


// Get part AABB
const IOGAabb& COGMesh::GetAABB (unsigned int _Part) const 
{
    return *(m_SubMeshes[_Part].aabb);
}


// Get ray intersection
bool COGMesh::GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos)
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


// check if active point.
bool COGMesh::IsActivePoint (unsigned int _Id)
{
    char active_point_marker[] = "actpoint";
    SPODNode* pNode = &m_pScene->pNode[_Id];
    if (strstr(pNode->pszName, active_point_marker) == pNode->pszName)
    {
        return true;
    }
    return false;
}


// get sub-mesh type.
SubMeshType COGMesh::GetSubMeshType (unsigned int _Id)
{
    SPODNode* pNode = &m_pScene->pNode[_Id];

	char propeller_prefix[] = "propeller";
    if (strstr(pNode->pszName, propeller_prefix) == pNode->pszName)
    {
        return OG_SUBMESH_PROPELLER;
    }

	return OG_SUBMESH_BODY;
}
