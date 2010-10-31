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
	m_BuffersList.reserve(m_pScene->nNumMeshNode);
    m_PartList.reserve(m_pScene->nNumMeshNode);
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

    		m_BuffersList.push_back(NULL);
            continue;
        }
		IOGVertexBuffers* pBuffer = m_pRenderer->CreateVertexBuffer(&m_pScene->pMesh[i]);
		m_BuffersList.push_back(pBuffer);
        m_PartList.push_back(i);
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

	std::vector<IOGVertexBuffers*>::iterator iter = m_BuffersList.begin();
    for (; iter != m_BuffersList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_BuffersList.clear();
    m_PartList.clear();

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGMesh::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (_Frame > m_pScene->nNumFrame)
		return;

    std::vector<unsigned int>::iterator iter = m_PartList.begin();
    for (; iter != m_PartList.end(); ++iter)
	{
		RenderPart(_mWorld, (*iter), _Frame);
	}
}


// Render part of the mesh.
void COGMesh::RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame)
{
	m_pScene->SetFrame((float)_Frame);
	const SPODNode& node = m_pScene->pNode[_Part];

    // Gets the node model matrix
    MATRIX mNodeWorld;
    m_pScene->GetWorldMatrix(mNodeWorld, node);

    // Multiply on the global world transform
    MATRIX mModel;
    MatrixMultiply(mModel, mNodeWorld, _mWorld);

    m_pRenderer->SetModelMatrix(mModel);
    m_pRenderer->RenderMesh(m_BuffersList[_Part]);
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

	m_AabbList.reserve(m_pScene->nNumMeshNode);
    m_Faces.reserve(4096);
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

		IOGAabb aabb = IOGAabb(vMinCorner, vMaxCorner);
		m_AabbList.push_back(aabb);
		m_AABB.EmbraceAABB(aabb);
	}
}


// Get combined AABB
const IOGAabb& COGMesh::GetAABB () const
{
	return m_AABB;
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
bool COGMesh::IsActivePoint (unsigned int _Part)
{
    char active_point_marker[] = "actpoint";
    SPODNode* pNode = &m_pScene->pNode[_Part];
    if (strstr(pNode->pszName, active_point_marker) == pNode->pszName)
    {
        return true;
    }
    return false;
}
