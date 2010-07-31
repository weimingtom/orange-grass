/*
 *  mesh.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 06.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogmesh.h"
#include "IOGMath.h"


COGMesh::COGMesh () :	m_pVBO (NULL),
						m_pIndexVBO (NULL),
						m_pScene (NULL)
{
	m_pScene = (CPVRTModelPOD*)malloc(sizeof(CPVRTModelPOD));
	memset(m_pScene, 0, sizeof(CPVRTModelPOD));
}


COGMesh::~COGMesh()
{
	if (m_pScene)
	{
		m_pScene->Destroy();
		free(m_pScene);
		m_pScene = NULL;
	}
	
	OG_SAFE_DELETE_ARRAY (m_pVBO);
	OG_SAFE_DELETE_ARRAY (m_pIndexVBO);
}


bool COGMesh::Load ()
{	
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

	if (!m_pScene->ReadFromFile(m_pResourceFile))
	{
		return false;
	}
	
	m_pVBO = new GLuint[m_pScene->nNumMesh];
	m_pIndexVBO = new GLuint[m_pScene->nNumMesh];
	
	glGenBuffers(m_pScene->nNumMesh, m_pVBO);
	
	for(unsigned int i = 0; i < m_pScene->nNumMesh; ++i)
	{
		// Load vertex data into buffer object
		SPODMesh& curMesh = m_pScene->pMesh[i];
		unsigned int uiSize = curMesh.nNumVertex * curMesh.sVertex.nStride;
		
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[i]);
		glBufferData(GL_ARRAY_BUFFER, uiSize, curMesh.pInterleaved, GL_STATIC_DRAW);
		
		// Load index data into buffer object if available
		m_pIndexVBO[i] = 0;
		if(curMesh.sFaces.pData)
		{
			glGenBuffers(1, &m_pIndexVBO[i]);
			uiSize = PVRTModelPODCountIndices(curMesh) * sizeof(GLshort);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, curMesh.sFaces.pData, GL_STATIC_DRAW);
		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	CalculateBounds();
    CalculateGeometry();

	m_LoadState = OG_RESSTATE_LOADED;

	return true;
}


void COGMesh::Render (const MATRIX& _mView)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		SPODNode* pNode = &m_pScene->pNode[i];
		
		// Gets the node model matrix
		MATRIX mWorld;
		m_pScene->GetWorldMatrix(mWorld, *pNode);
		
		// Multiply the view matrix by the model matrix to get the model-view matrix
		MATRIX mModelView;
		MatrixMultiply(mModelView, mWorld, _mView);
		glLoadMatrixf(mModelView.f);
				
		RenderObject(pNode->nIdx);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}


void COGMesh::RenderObject(unsigned int _id)
{
	SPODMesh& Mesh = m_pScene->pMesh[_id];
	
	// bind the VBO for the mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[_id]);
	// bind the index buffer, won't hurt if the handle is 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pIndexVBO[_id]);
	
	// Setup pointers
	glVertexPointer(3, VERTTYPEENUM, Mesh.sVertex.nStride, Mesh.sVertex.pData);
	if (Mesh.psUVW)
		glTexCoordPointer(2, VERTTYPEENUM, Mesh.psUVW[0].nStride, Mesh.psUVW[0].pData);
	glNormalPointer(VERTTYPEENUM, Mesh.sNormals.nStride, Mesh.sNormals.pData);
	
	if(Mesh.nNumStrips == 0)
	{
		if(m_pIndexVBO[_id])
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
			if(m_pIndexVBO[_id])
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


// calculate bounds
void COGMesh::CalculateBounds ()
{
	MATRIX mModel;
    Vec3 v, vMinCorner, vMaxCorner, vAABBMin, vAABBMax;

	m_AABBs.clear ();
	m_AABBs.reserve (m_pScene->nNumMesh);

	for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		SPODMesh& Mesh = m_pScene->pMesh[i];

        Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
		vMinCorner.x = vMaxCorner.x = pPtr->x; 
		vMinCorner.y = vMaxCorner.y = pPtr->y; 
		vMinCorner.z = vMaxCorner.z = pPtr->z;

        for (unsigned int j = 1; j < Mesh.nNumVertex; j++)
		{
			pPtr = (Vec3*)( (unsigned char*)(pPtr)+Mesh.sVertex.nStride);
            v.x = pPtr->x; v.y = pPtr->y; v.z = pPtr->z;

			if (v.x < vMinCorner.x) vMinCorner.x = v.x;
			if (v.y < vMinCorner.y) vMinCorner.y = v.y;
			if (v.z < vMinCorner.z) vMinCorner.z = v.z;
			if (v.x > vMaxCorner.x) vMaxCorner.x = v.x;
			if (v.y > vMaxCorner.y) vMaxCorner.y = v.y;
			if (v.z > vMaxCorner.z) vMaxCorner.z = v.z;
		}

		SPODNode* pNode = &m_pScene->pNode[i];
		m_pScene->GetWorldMatrix(mModel, *pNode);
		IOGAabb aabb (vMinCorner, vMaxCorner);
		aabb.UpdateTransform (mModel);
		m_AABBs.push_back (aabb);

		if (i==0)
		{
			vAABBMin = aabb.GetMin (); 
			vAABBMax = aabb.GetMax ();
		}
		else
		{
			const Vec3 vMin = aabb.GetMin ();
			const Vec3 vMax = aabb.GetMax ();
			if (vMin.x < vAABBMin.x) vAABBMin.x = vMin.x;
			if (vMin.y < vAABBMin.y) vAABBMin.y = vMin.y;
			if (vMin.z < vAABBMin.z) vAABBMin.z = vMin.z;
			if (vMax.x > vAABBMax.x) vAABBMax.x = vMax.x;
			if (vMax.y > vAABBMax.y) vAABBMax.y = vMax.y;
			if (vMax.z > vAABBMax.z) vAABBMax.z = vMax.z;
		}
	}

	m_CombinedAABB.SetMinMax (vAABBMin, vAABBMax);
}


// calculate geometry
void COGMesh::CalculateGeometry ()
{
	MATRIX mModel;
    Vec3 v;

    m_Faces.reserve(4096);
    for (unsigned int i=0; i<m_pScene->nNumMesh; ++i)
	{
		SPODNode* pNode = &m_pScene->pNode[i];
		m_pScene->GetWorldMatrix(mModel, *pNode);

        SPODMesh& Mesh = m_pScene->pMesh[i];

        Vec3* pPtr = (Vec3*)Mesh.pInterleaved;
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
                }
                m_Faces.push_back(face);
            }
        }
	}
}


// Get combined AABB
const IOGAabb& COGMesh::GetAABB () const
{
	return m_CombinedAABB;
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
