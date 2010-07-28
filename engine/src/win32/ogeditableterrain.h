/*
 *  ogeditableterrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGEDITABLETERRAIN_H_
#define OGEDITABLETERRAIN_H_

#include "OpenGL2.h"
#include "IOGEditableTerrain.h"
#include "Geometry.h"
#include "Mathematics.h"
#include "ogresource.h"


class COGEditableTerrain : public IOGEditableTerrain, public COGResource
{
	struct TVertex
	{
		Vec3	pos;
		Vec3	norm;
		Vec2	tex0;
		Vec4	color;
	};

public:
	COGEditableTerrain ();
	virtual ~COGEditableTerrain();

	// Load terrain.
	virtual bool Load ();
	
	// Save the terrain.
	virtual bool Save (const char* _pPath);

	// Set terrain position.
	virtual void SetWorldPosition (const Vec3& _vPos);

	// Set terrain texture.
	virtual void SetTexture (IOGTexture* _pTexture);

	// Render terrain.
	virtual void Render (const MATRIX& _mView);

	// Get type of the renderable.
	virtual RenderableType GetRenderableType () const { return OG_RENDERABLE_TERRAIN; }

	// Modify the heights of the vertices in the heighmap grid
	virtual void AddHeight (const Vec3& _vPos, int _patchsize, float _v, bool _bSmoothen);

	// Modify the color of the vertices in the heighmap grid
	virtual void ChangeColor (const Vec3& _vPos, int _patchsize, const Vec3& _color);

	// Get the array of vertices that are within the area of the patch
	virtual int GetPatch (const Vec3& _vPos, int _patchsize, Vec3* _pOut);

	// Smoothen the vertices that are within the area of the patch
	virtual void SmoothenPatch (const Vec3& _vPos, int _patchsize);

	// Get ray intersection
	virtual bool GetRayIntersection (const Vec3& _vRayPos, const Vec3& _vRayDir, Vec3* _pOutPos);
	
private:

	// Generate face normal.
	void GenerateFaceNormal (GLushort i1, GLushort i2, GLushort i3);

	// Update normals and (optionally) indices.
	void UpdateNormals ( bool _bUpdateIndices );

	// Smoothen normals.
	void SmoothenNormals ();

	// Get vertex from a heighmap grid
	TVertex* GetVertex (const Vec3& _vPos);

	// Get vertex from a heighmap grid
	TVertex* GetVertex (int _x, int _y);

	// Modify the heights of the vertex in the heighmap grid
	void AddHeight (int _x, int _y, float _v);

	// Modify the color of the vertex in the heighmap grid
	void ChangeBaseColor (int _x, int _y, const Vec3& _color, float _fFactor);

	// Update vertex normal
	void UpdateVertexNormal ( int _id, const Vec3& _updatedVec );

	// Update vertex normal
	void UpdateVertexNormal ( int _x, int _y, const Vec3& _updatedVec );

	// Rebuild VBO
	void RebuildVBO ();

	// Convert coords to index
	inline unsigned short CoordsToId ( int _x, int _y );

	// Check coordinate bounds
	inline bool CheckCoordBounds ( int _x, int _y );

	// World to grid position X
	inline int WorldToGrid_X ( const Vec3& _vPos );

	// World to grid position Y
	inline int WorldToGrid_Y ( const Vec3& _vPos );
	
private:
	// Vertex Buffer Object (VBO) handles
	GLuint		m_VBO;
	GLuint		m_IndexVBO;
	char*		m_pMap;
	GLushort*	m_pIndices;
	TVertex*	m_pVertices;
	Vec3*		m_pColors;
	IOGTexture*	m_pTexture;
	int			m_NumLayers;
	int			m_Width; 
	int			m_Height;
	Vec3		m_vPosition;

	static const int	g_Width;
	static const int	g_Height;
	static const float	g_fStep;
	static const float	g_fHeightScale;
	static const float	g_fMaxHeight;
	static const float	g_fAttentuation;
	static const Vec3	g_BaseColor;
};


// Convert coords to index
inline unsigned short COGEditableTerrain::CoordsToId ( int _x, int _y )
{
	return _y * m_Width + _x;
}

// Check coordinate bounds
inline bool COGEditableTerrain::CheckCoordBounds ( int _x, int _y )
{
	return !(_x < 0 || _y < 0 || _x > m_Width - 1 || _y > m_Height - 1);
}


// World to grid position X
inline int COGEditableTerrain::WorldToGrid_X ( const Vec3& _vPos )
{
	return (int)((_vPos.x - m_vPosition.x) / COGEditableTerrain::g_fStep);
}


// World to grid position Y
inline int COGEditableTerrain::WorldToGrid_Y ( const Vec3& _vPos )
{
	return (int)((_vPos.z - m_vPosition.z) / COGEditableTerrain::g_fStep);
}


#endif
