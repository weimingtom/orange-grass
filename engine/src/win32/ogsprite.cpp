/*
 *  ogsprite.mm
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "ogsprite.h"
#include "common.h"


COGSprite::COGSprite() :	m_pTexture(NULL),
							m_VBOHandle(0),
							m_fX(0.0f),
							m_fY(0.0f)
{
}


COGSprite::~COGSprite()
{
	m_pTexture = NULL;
	m_VBOHandle = 0;
}


// Initialize sprite.
void COGSprite::Init (IOGTexture* _pTexture)
{
	m_pTexture = _pTexture;
	MatrixOrthoRH(m_mOrthoProj, SCR_HEIGHT, SCR_WIDTH, -1, 1, 1);
}


// Set position.
void COGSprite::SetPosition (float _fX, float _fY, float _fWidth, float _fHeight)
{
	m_fX = _fX;
	m_fY = _fY;
	m_fWidth = _fWidth;
	m_fHeight = _fHeight;
	float fHalfScrWidth = SCR_WIDTH / 2.0f;
	float fHalfScrHeight = SCR_HEIGHT / 2.0f;

	m_Vertices[0] = -fHalfScrWidth+m_fWidth+m_fX;	m_Vertices[1] = fHalfScrHeight-m_fHeight-m_fY;	m_Vertices[2] = 0.0f;  m_Vertices[3] = 0.0f;  m_Vertices[4] = 1.0f;
	m_Vertices[5] = -fHalfScrWidth+m_fX;			m_Vertices[6] = fHalfScrHeight-m_fHeight-m_fY;	m_Vertices[7] = 0.0f;  m_Vertices[8] = 0.0f;  m_Vertices[9] = 0.0f;
	m_Vertices[10] = -fHalfScrWidth+m_fWidth+m_fX;	m_Vertices[11] = fHalfScrHeight-m_fY;			m_Vertices[12] = 0.0f; m_Vertices[13] = 1.0f; m_Vertices[14] = 1.0f;
	m_Vertices[15] = -fHalfScrWidth+m_fX;			m_Vertices[16] = fHalfScrHeight-m_fY;			m_Vertices[17] = 0.0f; m_Vertices[18] = 1.0f; m_Vertices[19] = 0.0f;

	glGenBuffers(1, &m_VBOHandle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
	unsigned int uiSize = 4 * (sizeof(GLfloat) * 5);
	glBufferData(GL_ARRAY_BUFFER, uiSize, m_Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// Render sprite.
void COGSprite::Render ()
{
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixf(m_mOrthoProj.f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glActiveTexture( GL_TEXTURE0 );
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_pTexture->GetTextureId());
	
	// Bind the VBO so we can fill it with data
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOHandle);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 20, 0);	// Stride = 20 bytes
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
	glTexCoordPointer(2, GL_FLOAT, 20, (void *)12);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glDrawArrays(GL_TRIANGLE_STRIP,  0, 4);
	glEnable(GL_DEPTH_TEST);
}
