/*
 *  ogeditableterrain.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "ogeditableterrain.h"
#include "IOGMath.h"


const int COGEditableTerrain::g_Width = 128;
const int COGEditableTerrain::g_Height = 512;
const float COGEditableTerrain::g_fStep = 17.0f;
const float COGEditableTerrain::g_fHeightScale = 1.4f;
const float COGEditableTerrain::g_fMaxHeight = COGEditableTerrain::g_fHeightScale * 255.0f;
const float COGEditableTerrain::g_fAttentuation = 0.5f;
const Vec3 COGEditableTerrain::g_BaseColor (0.5f, 0.8f, 0.1f);


COGEditableTerrain::COGEditableTerrain () :	m_VBO(0),
							m_IndexVBO(0),
							m_pMap(NULL),
							m_pIndices(NULL),
							m_pVertices(NULL),
							m_pColors(NULL),
							m_pTexture(NULL),
							m_Width(0),
							m_Height(0)
{
}


COGEditableTerrain::~COGEditableTerrain()
{
	OG_SAFE_DELETE_ARRAY (m_pMap);
	OG_SAFE_DELETE_ARRAY (m_pVertices);
	OG_SAFE_DELETE_ARRAY (m_pIndices);
	OG_SAFE_DELETE_ARRAY (m_pColors);
}


// Load terrain.
bool COGEditableTerrain::Load ()
{
	if (m_LoadState == OG_RESSTATE_UNKNOWN)
	{
		return false;
	}

	m_Width = g_Width;
	m_Height = g_Height;
	
	unsigned int numVertices = m_Width * m_Height;
	unsigned int numFaces = (m_Width-1) * (m_Height-1) * 2;
	m_pMap = new char [numVertices];
	m_pVertices = new TVertex [numVertices];
	m_pColors = new Vec3 [numVertices];
	m_pIndices = new GLushort [numFaces * 3];

	memset(m_pMap, 0, sizeof(numVertices));
	FILE* f = fopen(m_pResourceFile, "rb");
	fread(m_pMap, numVertices, 1, f);
	fclose(f);

	for (int j = 0, k = 0; j < m_Height; ++j)
	{
		for (int i = 0; i < m_Width; ++i)
		{
			m_pColors[k] = g_BaseColor;
			TVertex* pVertex = &m_pVertices[k++];
			pVertex->pos.x = m_vPosition.x + (GLfloat)i * g_fStep;
			pVertex->pos.y = m_vPosition.y + (m_pMap[CoordsToId(i, j)])*g_fHeightScale;
			pVertex->pos.z = m_vPosition.z + (GLfloat)j * g_fStep;
			pVertex->norm = Vec3(0.0f, 1.0f, 0.0f);
			pVertex->tex0 = Vec2((GLfloat)i, (GLfloat)j);
			pVertex->color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	UpdateNormals(true);
	
	glGenBuffers(1, &m_IndexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexVBO);
	unsigned int uiSize = numFaces * 3 * sizeof(GLushort);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiSize, m_pIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	m_LoadState = OG_RESSTATE_LOADED;

	return true;
}

	
// Save the terrain.
bool COGEditableTerrain::Save (const char* _pPath)
{
	int ChunkSize = 128;
	int numChunks = m_Height / ChunkSize;

	char** ppOutFiles = new char* [numChunks];
	for (int n = 0; n < numChunks; ++n)
	{
		ppOutFiles[n] = new char [OG_MAX_PATH];
		sprintf (ppOutFiles[n], "%s\\terrain_%d.ogt", _pPath, n);
	}

	for (int n = 0; n < numChunks; ++n)
	{
		FILE* chunkFile = fopen(ppOutFiles[n], "wb");
		int chunkOffset = n * ChunkSize;
		for (int j = 0; j < ChunkSize; ++j)
		{
			for (int i = 0; i < m_Width; ++i)
			{
				int id = CoordsToId(i, j + chunkOffset);
				TVertex* pVertex = &m_pVertices[id];
				fwrite (pVertex, sizeof (TVertex), 1, chunkFile);
			}
		}
		fclose (chunkFile);
	}

	for (int n = 0; n < numChunks; ++n)
	{
		OG_SAFE_DELETE_ARRAY(ppOutFiles[n]);
	}
	OG_SAFE_DELETE_ARRAY (ppOutFiles);

	return true;
}


// Set terrain position.
void COGEditableTerrain::SetWorldPosition (const Vec3& _vPos)
{
	m_vPosition = _vPos;
}


// Set terrain texture.
void COGEditableTerrain::SetTexture (IOGTexture* _pTexture)
{
	m_pTexture = _pTexture;
}


// Render terrain.
void COGEditableTerrain::Render (const MATRIX& _mView)
{
	glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

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

	glEnable (GL_BLEND); 
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureId());
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_SHORT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


// Generate face normal
void COGEditableTerrain::GenerateFaceNormal (GLushort i1, GLushort i2, GLushort i3)
{
	Vec3 v1 = m_pVertices[i1].pos;
	Vec3 v2 = m_pVertices[i2].pos;
	Vec3 v3 = m_pVertices[i3].pos;
	Vec3 p = v2-v1;
	Vec3 q = v3-v1;
	Vec3 n = q.cross(p);
	n.normalize();
	UpdateVertexNormal (i1, n);
	UpdateVertexNormal (i2, n);
	UpdateVertexNormal (i3, n);
}


// Smoothen normals.
void COGEditableTerrain::SmoothenNormals ()
{
	Vec3 vArr[9];
	TVertex* pVert = NULL;
	for (int j = 0; j < m_Height; ++j)
	{
		for (int i = 0; i < m_Width; ++i)
		{
			int affected = 0;
			pVert = GetVertex(i, j);     if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i-1, j-1); if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i-1, j);   if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i-1, j+1); if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i, j-1);   if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i, j+1);   if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i+1, j-1); if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i+1, j);   if (pVert) vArr[affected++] = pVert->norm;
			pVert = GetVertex(i+1, j+1); if (pVert) vArr[affected++] = pVert->norm;
			
			Vec3 smoothed = Vec3(0,0,0);
			for (int n = 0; n<affected; ++n)
				smoothed += vArr[n];
			smoothed /= (float)affected;
			UpdateVertexNormal(i, j, smoothed);
		}
	}
}


// Update vertex normal
void COGEditableTerrain::UpdateVertexNormal ( int _id, const Vec3& _updatedVec )
{
	TVertex* pVert = &m_pVertices [_id];
	pVert->norm = _updatedVec;
	float dp = MatrixVec3DotProduct(_updatedVec, Vec3(0, 1, 0)) * g_fAttentuation + 0.2f;
	OG_CLAMP (dp, 0.0f, 1.0f);
	pVert->color.x = m_pColors[_id].x * dp;
	pVert->color.y = m_pColors[_id].y * dp;
	pVert->color.z = m_pColors[_id].z * dp;
}


// Update vertex normal
void COGEditableTerrain::UpdateVertexNormal ( int _x, int _y, const Vec3& _updatedVec )
{
	if (!CheckCoordBounds(_x, _y))
		return;
	UpdateVertexNormal (CoordsToId(_x, _y), _updatedVec );
}


// Get vertex from a heighmap grid
COGEditableTerrain::TVertex* COGEditableTerrain::GetVertex (const Vec3& _vPos)
{
	int x = WorldToGrid_X(_vPos);
	int y = WorldToGrid_Y(_vPos);
	if (!CheckCoordBounds(x, y))
		return NULL;
	return GetVertex (x, y);
}


// Get vertex from a heighmap grid
COGEditableTerrain::TVertex* COGEditableTerrain::GetVertex (int _x, int _y)
{
	if (!CheckCoordBounds(_x, _y))
		return NULL;
	return &m_pVertices [CoordsToId(_x, _y)];
}


// Modify the heights of the vertex in the heighmap grid
void COGEditableTerrain::AddHeight (int _x, int _y, float _v)
{
	TVertex* pV = GetVertex (_x, _y);
	if (!pV)
		return;

	float fNewHeight = pV->pos.y + _v;
	if (fNewHeight > g_fMaxHeight)
		fNewHeight = g_fMaxHeight;
	else if (fNewHeight < 0.0f)
		fNewHeight = 0.0f;
	pV->pos.y = fNewHeight;
}


// Modify the heights of the vertices in the heighmap grid
void COGEditableTerrain::AddHeight (const Vec3& _vPos, int _patchsize, float _v, bool _bSmoothen)
{
	int x = WorldToGrid_X(_vPos);
	int y = WorldToGrid_Y(_vPos);
	if (!CheckCoordBounds(x, y))
		return;

	for (int dy = -_patchsize; dy <= _patchsize; ++dy)
	{
		for (int dx = -_patchsize; dx <= _patchsize; ++dx)
		{
			float fDist = Dist(x, y, x+dx, y+dy);
			if (fDist <= _patchsize)
			{
				float ff = fDist / (float)_patchsize;
				AddHeight ( x+dx, y+dy, _v * cosf(ff) );
			}
		}
	}

	if (_bSmoothen)
		SmoothenPatch (_vPos, _patchsize);

	UpdateNormals (false);
}


// Get the array of vertices that are within the area of the patch
int COGEditableTerrain::GetPatch (const Vec3& _vPos, int _patchsize, Vec3* _pOut)
{
	int x = WorldToGrid_X(_vPos);
	int y = WorldToGrid_Y(_vPos);
	if (!CheckCoordBounds(x, y))
		return 0;

	int NumPatchVerts = 0;
	for (int dy = -_patchsize; dy <= _patchsize; ++dy)
	{
		for (int dx = -_patchsize; dx <= _patchsize; ++dx)
		{
			float fDist = Dist(x, y, x+dx, y+dy);
			if (fDist <= _patchsize)
			{
				TVertex* pV = GetVertex (x+dx, y+dy);
				if (pV)
				{
					_pOut[NumPatchVerts++] = pV->pos;
				}
			}
		}
	}
	return NumPatchVerts;
}


// Smoothen the vertices that are within the area of the patch
void COGEditableTerrain::SmoothenPatch (const Vec3& _vPos, int _patchsize)
{
	int x = WorldToGrid_X(_vPos);
	int y = WorldToGrid_Y(_vPos);
	if (!CheckCoordBounds(x, y))
		return;

	int max_x = x + _patchsize;
	int max_y = y + _patchsize;
	for (int j = y-_patchsize; j <= max_y; ++j)
	{
		for (int i = x-_patchsize; i <= max_x; ++i)
		{
			TVertex* pCV = GetVertex(i, j);
			if (!pCV)
				continue;

			int affected = 0;
			float avg = 0.0f;

			for (int jj = -1; jj <= 1; ++jj)
			{
				for (int ii = -1; ii <= 1; ++ii)
				{
					TVertex* pV = GetVertex(i+ii, j+jj);
					if (pV)
					{
						avg += pV->pos.y;
						++affected;
					}
				}
			}

			avg /= affected;
			pCV->pos.y = avg;
		}
	}
}


// Update normals and (optionally) indices.
void COGEditableTerrain::UpdateNormals ( bool _bUpdateIndices )
{
	int indWidth = m_Width-1;
	int indHeight = m_Height-1;
	int kk = 0;
	for (int j = 0; j < indHeight; ++j)
	{
		for (int i = 0; i < indWidth; ++i)
		{
			GLushort face1_1 = CoordsToId(i, j);
			GLushort face1_2 = CoordsToId(i+1, j);
			GLushort face1_3 = CoordsToId(i+1, j+1);
			GLushort face2_2 = CoordsToId(i, j+1);

			GenerateFaceNormal (face1_1, face1_2, face1_3);
			GenerateFaceNormal (face1_3, face2_2, face1_1);

			if (_bUpdateIndices)
			{
				m_pIndices[kk++] = face1_1;
				m_pIndices[kk++] = face1_2;
				m_pIndices[kk++] = face1_3;
				m_pIndices[kk++] = face1_3;
				m_pIndices[kk++] = face2_2;
				m_pIndices[kk++] = face1_1;
			}
		}
	}

	SmoothenNormals();

	RebuildVBO ();
}


// Get ray intersection
bool COGEditableTerrain::GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos)
{
	float t, u, v;
	bool bIntersected = false;
	unsigned int numIndices = (m_Width-1) * (m_Height-1) * 2 * 3;
	for (unsigned int i = 0; i < numIndices; i+=3)
	{
		GLushort id1 = m_pIndices[i];
		GLushort id2 = m_pIndices[i+1];
		GLushort id3 = m_pIndices[i+2];
		Vec3 p0 = m_pVertices[id1].pos;
		Vec3 p1 = m_pVertices[id2].pos;
		Vec3 p2 = m_pVertices[id3].pos;
		bIntersected = CheckTriangleIntersection (_vRayPos, _vRayDir, p0, p1, p2, &t, &u, &v );
		if (bIntersected)
		{
			*_pOutPos = Barycentric2World(u, v, p0, p1, p2);
			return true;
		}
	}
	return false;
}


// Modify the color of the vertices in the heighmap grid
void COGEditableTerrain::ChangeColor (const Vec3& _vPos, int _patchsize, const Vec3& _color)
{
	int x = WorldToGrid_X(_vPos);
	int y = WorldToGrid_Y(_vPos);
	if (!CheckCoordBounds(x, y))
		return;

	for (int dy = -_patchsize; dy <= _patchsize; ++dy)
	{
		for (int dx = -_patchsize; dx <= _patchsize; ++dx)
		{
			float fDist = Dist(x, y, x+dx, y+dy);
			if (fDist <= _patchsize)
			{
				float fFactor = sinf(fDist / (float)_patchsize);
				ChangeBaseColor ( x+dx, y+dy, _color, fFactor );
			}
		}
	}

	RebuildVBO ();
}


// Modify the color of the vertex in the heighmap grid
void COGEditableTerrain::ChangeBaseColor (int _x, int _y, const Vec3& _color, float _fFactor)
{
	TVertex* pVert = GetVertex(_x, _y);
	if (pVert)
	{
		int id = CoordsToId(_x, _y);
		Vec3 old_color = m_pColors[id];
		m_pColors[id] = Vec3Lerp(_fFactor, _color, old_color);
		UpdateVertexNormal (id, pVert->norm);
	}
}


// Rebuild VBO
void COGEditableTerrain::RebuildVBO ()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	unsigned int uiSize = (m_Width * m_Height) * sizeof(TVertex);
	glBufferData(GL_ARRAY_BUFFER, uiSize, m_pVertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
