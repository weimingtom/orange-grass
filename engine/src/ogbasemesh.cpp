/*
 *  ogbasemesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogbasemesh.h"
#include "OrangeGrass.h"


COGBaseMesh::COGBaseMesh () : m_pScene (NULL)
{
    m_NumParts = 0;
}


COGBaseMesh::~COGBaseMesh()
{
	Unload();
}


// Load resource
bool COGBaseMesh::Load ()
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

	m_pScene = new CPVRTModelPOD();
	if (!m_pScene->ReadFromFile(m_ResourceFile.c_str()))
	{
        OG_LOG_ERROR("Failed to load mesh from file %s", m_ResourceFile.c_str());
		return false;
	}
	
    m_NumParts = 0;
    m_SubMeshes.reserve(m_pScene->nNumMeshNode);

    LoadSubMeshes();

    CalculateGeometry();

    m_LoadState = OG_RESSTATE_LOADED;

    return true;
}


// Unload resource.
void COGBaseMesh::Unload ()
{
    if (m_LoadState != OG_RESSTATE_LOADED)
    {
        return;
    }

	OG_SAFE_DELETE(m_pScene);
    m_Faces.clear();
    m_AABB.SetMinMax(Vec3(0,0,0), Vec3(0,0,0));

    std::vector<SubMesh>::iterator iter = m_SubMeshes.begin();
    for (; iter != m_SubMeshes.end(); ++iter)
    {
        OG_SAFE_DELETE((*iter).buffer);
        OG_SAFE_DELETE((*iter).aabb);
    }
    m_SubMeshes.clear();

    UnloadSubMeshes();

	m_NumParts = 0;
	m_LoadState = OG_RESSTATE_DEFINED;
}


// calculate geometry
void COGBaseMesh::CalculateGeometry ()
{
	MATRIX mModel;
    Vec3 v, vMinCorner, vMaxCorner;

    m_Faces.reserve(4096);
    unsigned int Part = 0;
    for (unsigned int i=0; i < m_pScene->nNumMeshNode; ++i)
	{
        if (GetSubMeshType(i) == OG_SUBMESH_ACTPOINT)
            continue;

        m_pScene->SetFrame(0);
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


// Get all submesh AABBs
void COGBaseMesh::GetAllAABBs (std::vector<IOGAabb*>& _aabbs)
{
    _aabbs.reserve(m_SubMeshes.size());
    std::vector<SubMesh>::iterator iter = m_SubMeshes.begin();
    for (; iter != m_SubMeshes.end(); ++iter)
    {
        _aabbs.push_back((*iter).aabb);
    }
}


// Get ray intersection
bool COGBaseMesh::GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos)
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


// get sub-mesh type.
SubMeshType COGBaseMesh::GetSubMeshType (unsigned int _Id)
{
    SPODNode* pNode = &m_pScene->pNode[_Id];

    if (strstr(pNode->pszName, "propeller") == pNode->pszName)
    {
        return OG_SUBMESH_PROPELLER;
    }
    else if (strstr(pNode->pszName, "actpoint") == pNode->pszName)
    {
        return OG_SUBMESH_ACTPOINT;
    }
    return OG_SUBMESH_BODY;
}
