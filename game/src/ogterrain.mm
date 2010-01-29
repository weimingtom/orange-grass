/*
 *  ogterrain.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ogterrain.h"


COGTerrain::COGTerrain () :	m_VBO(0),
							m_IndexVBO(0),
							m_pMap(NULL),
							m_pIndices(NULL),
							m_pVertices(NULL),
							m_NumLayers(0),
							m_Width(0),
							m_Height(0)
{
	memset(m_pTextures, 0, sizeof(IOGTexture*) * 3);
}


COGTerrain::~COGTerrain()
{
	if (m_pMap)
	{
		delete [] m_pMap;
		m_pMap = NULL;
	}

	if (m_pVertices)
	{
		delete[] m_pVertices;
		m_pVertices = NULL;
	}
	
	if (m_pIndices)
	{
		delete[] m_pIndices;
		m_pIndices = NULL;
	}
}


// Load terrain.
bool COGTerrain::Load (const char* _pTerrainFile, int _Width, int _Height)
{
	m_Width = _Width;
	m_Height = _Height;
	
	unsigned int numVertices = m_Width * m_Height;
	unsigned int numFaces = (m_Width-1) * (m_Height-1) * 2;
	m_pMap = new char [numVertices];
	m_pVertices = new TVertex [numVertices];
	m_pIndices = new GLshort [numFaces * 3];
	if (_pTerrainFile != NULL)
	{
		memset(m_pMap, 0, sizeof(numVertices));
		FILE* f = fopen(_pTerrainFile, "rb");
		fread(this->m_pMap, numVertices, 1, f);
		fclose(f);
	}

	float fScale = 15.0f;
	unsigned int uiSize = 0;
	int k = 0;
	for (int j = 0; j < m_Height; ++j)
	{
		for (int i = 0; i < m_Width; ++i)
		{
			m_pVertices[k].pos.x = -(m_Width/2*fScale) + (GLfloat)i * fScale;
			m_pVertices[k].pos.y = (this->m_pMap[(j)*m_Width+i])*5.0f;
			m_pVertices[k].pos.z = (GLfloat)j * fScale;
			m_pVertices[k].norm.x = 0.0f;
			m_pVertices[k].norm.y = 0.0f;
			m_pVertices[k].norm.z = 1.0f;
			m_pVertices[k].tex0.x = (GLfloat)i;
			m_pVertices[k].tex0.y = (GLfloat)j;
			m_pVertices[k].color.x = 1.0f;
			m_pVertices[k].color.y = 0.2f;
			m_pVertices[k].color.z = 0.2f;
			m_pVertices[k].color.w = 1.0f;
			++k;
		}
	}
	
	int indWidth = m_Width-1;
	int indHeight = m_Height-1;
	int kk = 0;
	for (int ij = 0; ij < indHeight; ++ij)
	{
		for (int ii = 0; ii < indWidth; ++ii)
		{
			GLshort face1_1 = (GLshort)((ij)*m_Width+ii);
			GLshort face1_2 = (GLshort)((ij+1)*m_Width+ii);
			GLshort face1_3 = (GLshort)((ij+1)*m_Width+ii+1);
			GLshort face2_1 = (GLshort)((ij+1)*m_Width+ii+1);
			GLshort face2_2 = (GLshort)((ij)*m_Width+ii+1);
			GLshort face2_3 = (GLshort)((ij)*m_Width+ii);

			GenerateFaceNormal (face1_1, face1_2, face1_3);
			GenerateFaceNormal (face2_1, face2_2, face2_3);
			
			m_pIndices[kk++] = face1_1;
			m_pIndices[kk++] = face1_2;
			m_pIndices[kk++] = face1_3;
			m_pIndices[kk++] = face2_1;
			m_pIndices[kk++] = face2_2;
			m_pIndices[kk++] = face2_3;
		}
	}
	
	SmoothenNormals();

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	uiSize = numVertices * sizeof(TVertex);
	glBufferData(GL_ARRAY_BUFFER, uiSize, m_pVertices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &m_IndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexVBO);
	uiSize = numFaces * 3 * sizeof(GLshort);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, m_pIndices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}


// Set terrain texture layer.
void COGTerrain::SetTextureLayer (IOGTexture* _pTexture)
{
	m_pTextures[m_NumLayers++] = _pTexture;
}


// Render terrain.
void COGTerrain::Render (const MATRIX& _mView)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ZERO, GL_SRC_COLOR);
	
	unsigned int numFaces = (m_Width-1) * (m_Height-1) * 2;
	unsigned int vertStride = sizeof(TVertex);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IndexVBO);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, vertStride, 0);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, vertStride, (void*)12);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, vertStride, (void*)24);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, vertStride, (void*)32);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(_mView.f);

	for (int texlayer = 0; texlayer < m_NumLayers; ++texlayer)
	{
		glBindTexture(GL_TEXTURE_2D, m_pTextures[texlayer]->GetTextureId());
		glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_SHORT, 0);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_BLEND);
}


// Generate face normal
void COGTerrain::GenerateFaceNormal (GLshort i1, GLshort i2, GLshort i3)
{
	Vec3 v1 = m_pVertices[i1].pos;
	Vec3 v2 = m_pVertices[i2].pos;
	Vec3 v3 = m_pVertices[i3].pos;
	Vec3 p = v2-v1;
	Vec3 q = v3-v1;
	Vec3 n = p.cross(q);
	n.normalize();
	m_pVertices[i1].norm = n;
	m_pVertices[i2].norm = n;
	m_pVertices[i3].norm = n;
}


// Smoothen normals.
void COGTerrain::SmoothenNormals ()
{
	Vec3 vArr[9];
	for (int j = 0; j < m_Height; ++j)
	{
		for (int i = 0; i < m_Width; ++i)
		{
			int affected = 0;
			vArr[affected++] = m_pVertices[(j)*m_Width+i].norm;
			if (i>0 && j>0)
				vArr[affected++] = m_pVertices[(j-1)*m_Width+(i-1)].norm;
			if (j>0)
				vArr[affected++] = m_pVertices[(j-1)*m_Width+(i)].norm;
			if (i<m_Width-1 && j>0)
				vArr[affected++] = m_pVertices[(j-1)*m_Width+(i+1)].norm;
			if (i>0)
				vArr[affected++] = m_pVertices[(j)*m_Width+(i-1)].norm;
			if (i<m_Width-1)
				vArr[affected++] = m_pVertices[(j)*m_Width+(i+1)].norm;
			if (i>0 && j<m_Height-1)
				vArr[affected++] = m_pVertices[(j+1)*m_Width+(i-1)].norm;
			if (j<m_Height-1)
				vArr[affected++] = m_pVertices[(j+1)*m_Width+(i)].norm;
			if (i<m_Width-1 && j<m_Height-1)
				vArr[affected++] = m_pVertices[(j+1)*m_Width+(i+1)].norm;
			
			Vec3 smoothed = Vec3(0,0,0);
			for (int n = 0; n<affected; ++n)
				smoothed += vArr[n];
			smoothed /= affected;
			m_pVertices[j*m_Width+i].norm = smoothed;
		}
	}
}
