/*
 *  ogterrain.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTERRAIN_H_
#define OGTERRAIN_H_

#include "IOGTerrain.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "common.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "Mathematics.h"


class COGTerrain : public IOGTerrain
{
	struct TVertex
	{
		Vec3	pos;
		Vec3	norm;
		Vec2	tex0;
		Vec4	color;
	};
	
public:
	COGTerrain ();
	virtual ~COGTerrain();
		
	// Load terrain.
	virtual bool Load (const char* _pTerrainFile, int _Width, int _Height);
	
	// Set terrain texture layer.
	virtual void SetTextureLayer (IOGTexture* _pTexture);
	
	// Render terrain.
	virtual void Render (const MATRIX& _mView);
	
private:
	
	// Generate face normal.
	void GenerateFaceNormal (GLshort i1, GLshort i2, GLshort i3);
	
	// Smoothen normals.
	void SmoothenNormals ();
	
private:
	// Vertex Buffer Object (VBO) handles
	GLuint		m_VBO;
	GLuint		m_IndexVBO;
	char*		m_pMap;
	GLshort*	m_pIndices;
	TVertex*	m_pVertices;
	IOGTexture*	m_pTextures[3];
	int			m_NumLayers;
	int			m_Width; 
	int			m_Height;
};


#endif
