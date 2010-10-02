/*
 *  ogmesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogmesh.h"
#include "IOGMath.h"
#include "OrangeGrass.h"


COGMesh::COGMesh () :	m_pScene (NULL)
{
    m_pRenderer = GetRenderer();
	m_pScene = (CPVRTModelPOD*)malloc(sizeof(CPVRTModelPOD));
	memset(m_pScene, 0, sizeof(CPVRTModelPOD));
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
	
	m_BuffersList.reserve(m_pScene->nNumMesh);
	for(unsigned int i = 0; i < m_pScene->nNumMesh; ++i)
	{
		COGVertexBuffers* pBuffer = new COGVertexBuffers(&m_pScene->pMesh[i]);
		m_BuffersList.push_back(pBuffer);
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

	std::vector<COGVertexBuffers*>::iterator iter = m_BuffersList.begin();
    for (; iter != m_BuffersList.end(); ++iter)
    {
		OG_SAFE_DELETE((*iter));
	}
	m_BuffersList.clear();

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render mesh.
void COGMesh::Render (const MATRIX& _mWorld, unsigned int _Frame)
{
	if (_Frame < m_pScene->nNumFrame)
		return;

	for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		RenderPart(_mWorld, i, _Frame);
	}
}


// Render part of the mesh.
void COGMesh::RenderPart (const MATRIX& _mWorld, unsigned int _Part, unsigned int _Frame)
{
    if (_Part > GetNumRenderables() || _Frame < m_pScene->nNumFrame)
        return;

	m_pScene->SetFrame((float)_Frame);
	const SPODNode& node = m_pScene->pNode[_Part];

    // Gets the node model matrix
    MATRIX mNodeWorld;
    m_pScene->GetWorldMatrix(mNodeWorld, node);

    // Multiply on the global world transform
    MATRIX mModel;
    MatrixMultiply(mModel, mNodeWorld, _mWorld);

    m_pRenderer->SetModelMatrix(mModel);
    m_pRenderer->RenderMesh(m_BuffersList[node.nIdx]);
}


// Get num renderable parts.
unsigned int COGMesh::GetNumRenderables () const
{
    return m_pScene->nNumMesh;
}


// calculate geometry
void COGMesh::CalculateGeometry ()
{
	MATRIX mModel;
    Vec3 v, vMinCorner, vMaxCorner;

    bool bFirstVertexProcessed = false;

    m_Faces.reserve(4096);
    for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		SPODNode* pNode = &m_pScene->pNode[i];
		m_pScene->GetWorldMatrix(mModel, *pNode);

        SPODMesh& Mesh = m_pScene->pMesh[i];

        Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
		
        if (!bFirstVertexProcessed)
        {
            vMinCorner.x = vMaxCorner.x = pPtr->x; 
            vMinCorner.y = vMaxCorner.y = pPtr->y; 
            vMinCorner.z = vMaxCorner.z = pPtr->z;
            MatrixVecMultiply(vMinCorner, vMinCorner, mModel);
            MatrixVecMultiply(vMaxCorner, vMaxCorner, mModel);
            bFirstVertexProcessed = true;
        }

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

                    VECTOR4 v_in, v_out;
                    v_in.x = face.vertices[k].x; v_in.y = face.vertices[k].y; v_in.z = face.vertices[k].z; v_in.w = 1.0f;
                    MatrixVec4Multiply(v_out, v_in, mModel);
                    face.vertices[k].x = v_out.x; face.vertices[k].y = v_out.y; face.vertices[k].z = v_out.z;

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
	}

    m_AABB.SetMinMax (vMinCorner, vMaxCorner);
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
