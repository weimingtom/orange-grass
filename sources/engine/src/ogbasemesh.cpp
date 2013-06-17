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


// Update submesh (for tools)
void COGBaseMesh::UpdateSubMesh (unsigned int _Id, const OGSubMesh& _SubMesh)
{
    // TBD
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
    m_AABB.SetMinMax(OGVec3(0,0,0), OGVec3(0,0,0));

    std::vector<OGSubMesh>::iterator iter = m_SubMeshes.begin();
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
	OGMatrix mModel;
    OGVec3 v, vMinCorner, vMaxCorner;

    m_Faces.reserve(4096);
    unsigned int Part = 0;
    for (unsigned int i=0; i < m_pScene->nNumMeshNode; ++i)
	{
        SPODNode* pNode = &m_pScene->pNode[i];
        if (ParseSubMeshType(pNode->pszName) == OG_SUBMESH_ACTPOINT)
            continue;

        m_pScene->SetFrame(0);
		m_pScene->GetWorldMatrix(mModel, *pNode);

        SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];

        OGVec3* pPtr = (OGVec3*)Mesh.pInterleaved;
		
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
                    face.vertices[k] = *((OGVec3*)((unsigned char*)(pPtr)+Mesh.sVertex.nStride * ind));

                    OGVec3& v_out = face.vertices[k];
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


// Get ray intersection
bool COGBaseMesh::GetRayIntersection (const OGVec3& _vRayPos, const OGVec3& _vRayDir, OGVec3* _pOutPos)
{
	float t, u, v;
	bool bIntersected = false;
    unsigned int numFaces = m_Faces.size();
	for (unsigned int i = 0; i < numFaces; ++i)
	{
        OGVec3 p0 = m_Faces[i].vertices[0];
        OGVec3 p1 = m_Faces[i].vertices[1];
        OGVec3 p2 = m_Faces[i].vertices[2];
		bIntersected = CheckTriangleIntersection (_vRayPos, _vRayDir, p0, p1, p2, &t, &u, &v );
		if (bIntersected)
		{
			*_pOutPos = Barycentric2World(u, v, p0, p1, p2);
			return true;
		}
	}
	return false;
}


// convert mesh to an internal format
void COGBaseMesh::ConvertMesh ()
{
	OGMatrix mModel;
    OGVec3 v, vMinCorner, vMaxCorner;

    m_Faces.reserve(4096);
    unsigned int Part = 0;
    for (unsigned int i=0; i < m_pScene->nNumMeshNode; ++i)
	{
        if (m_SubMeshes[Part].type == OG_SUBMESH_ACTPOINT)
            continue;

        m_pScene->SetFrame(0);
        SPODNode* pNode = &m_pScene->pNode[i];
		m_pScene->GetWorldMatrix(mModel, *pNode);

        SPODMesh& Mesh = m_pScene->pMesh[pNode->nIdx];

        OGVec3* pPtr = (OGVec3*)Mesh.pInterleaved;
		
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
                    face.vertices[k] = *((OGVec3*)((unsigned char*)(pPtr)+Mesh.sVertex.nStride * ind));

                    OGVec3& v_out = face.vertices[k];
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
