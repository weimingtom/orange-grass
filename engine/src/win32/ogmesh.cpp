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


COGMesh::COGMesh () :	//m_pVBO (NULL),
						//m_pIndexVBO (NULL),
						m_pScene (NULL)
{
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
	
	//m_pVBO = new GLuint[m_pScene->nNumMesh];
	//m_pIndexVBO = new GLuint[m_pScene->nNumMesh];
	//glGenBuffers(m_pScene->nNumMesh, m_pVBO);
	
	for(unsigned int i = 0; i < m_pScene->nNumMesh; ++i)
	{
		COGVertexBuffers* pBuffer = new COGVertexBuffers(&m_pScene->pMesh[i]);
		m_BuffersList.push_back(pBuffer);

		//// Load vertex data into buffer object
		//SPODMesh& curMesh = m_pScene->pMesh[i];
		//unsigned int uiSize = curMesh.nNumVertex * curMesh.sVertex.nStride;
		//
		//glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[i]);
		//glBufferData(GL_ARRAY_BUFFER, uiSize, curMesh.pInterleaved, GL_STATIC_DRAW);
		//
		//// Load index data into buffer object if available
		//m_pIndexVBO[i] = 0;
		//if(curMesh.sFaces.pData)
		//{
		//	glGenBuffers(1, &m_pIndexVBO[i]);
		//	uiSize = PVRTModelPODCountIndices(curMesh) * sizeof(GLshort);
		//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[i]);
		//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, curMesh.sFaces.pData, GL_STATIC_DRAW);
		//}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

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
	//OG_SAFE_DELETE_ARRAY (m_pVBO);
	//OG_SAFE_DELETE_ARRAY (m_pIndexVBO);

	m_LoadState = OG_RESSTATE_DEFINED;
}


// Render.
void COGMesh::Render (const MATRIX& _mView)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	MATRIX mWorld, mModelView;

	for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		const SPODNode* pNode = &m_pScene->pNode[i];
		
		// Gets the node model matrix
		m_pScene->GetWorldMatrix(mWorld, *pNode);
		
		// Multiply the view matrix by the model matrix to get the model-view matrix
		MatrixMultiply(mModelView, mWorld, _mView);
		glLoadMatrixf(mModelView.f);
				
		RenderObject(pNode->nIdx);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Render.
void COGMesh::Render (const MATRIX& _mView, unsigned int _Part)
{
    if (_Part > GetNumRenderables() || _Part < 0)
        return;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    SPODNode* pNode = &m_pScene->pNode[_Part];

    // Gets the node model matrix
    MATRIX mWorld;
    m_pScene->GetWorldMatrix(mWorld, *pNode);

    // Multiply the view matrix by the model matrix to get the model-view matrix
    MATRIX mModelView;
    MatrixMultiply(mModelView, mWorld, _mView);
    glLoadMatrixf(mModelView.f);

    RenderObject(pNode->nIdx);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


// Get num renderable parts.
unsigned int COGMesh::GetNumRenderables () const
{
    return m_pScene->nNumMesh;
}


// Render the particular sub-object
void COGMesh::RenderObject(unsigned int _id)
{
	const SPODMesh& Mesh = m_pScene->pMesh[_id];
	
	//// bind the VBO for the mesh
	//glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[_id]);
	//// bind the index buffer, won't hurt if the handle is 0
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[_id]);
	//
	//// Setup pointers
	//glVertexPointer(3, VERTTYPEENUM, Mesh.sVertex.nStride, Mesh.sVertex.pData);
	//if (Mesh.psUVW)
	//	glTexCoordPointer(2, VERTTYPEENUM, Mesh.psUVW[0].nStride, Mesh.psUVW[0].pData);
	//glNormalPointer(VERTTYPEENUM, Mesh.sNormals.nStride, Mesh.sNormals.pData);
	COGVertexBuffers* pBuff = m_BuffersList[_id];
	pBuff->Apply();
	
	if(Mesh.nNumStrips == 0)
	{
		if(/*m_pIndexVBO[_id]*/pBuff->IsIndexed())
		{
			// Indexed Triangle list
			glDrawElements(GL_TRIANGLES, Mesh.nNumFaces * 3, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			// Non-Indexed Triangle list
			glDrawArrays(GL_TRIANGLES, 0, Mesh.nNumFaces * 3);
		}
	}
	else
	{
		for(unsigned int i = 0; i < Mesh.nNumStrips; ++i)
		{
			int offset = 0;
			if(/*m_pIndexVBO[_id]*/pBuff->IsIndexed())
			{
				// Indexed Triangle strips
				glDrawElements(GL_TRIANGLE_STRIP, Mesh.pnStripLength[i]+2, GL_UNSIGNED_SHORT, &((GLshort*)0)[offset]);
			}
			else
			{
				// Non-Indexed Triangle strips
				glDrawArrays(GL_TRIANGLE_STRIP, offset, Mesh.pnStripLength[i]+2);
			}
			offset += Mesh.pnStripLength[i]+2;
		}
	}
	
	// unbind the vertex buffers as we don't need them bound anymore
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
