/*
 *  ogsprite.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 08.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGSPRITE_H_
#define OGSPRITE_H_

#include "IOGSprite.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "common.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "Mathematics.h"


class COGSprite : public IOGSprite
{
public:
	COGSprite();
	virtual ~COGSprite();
		
	// Initialize sprite.
	virtual void Init (IOGTexture* _pTexture);
	
	// Set position.
	virtual void SetPosition (float _fX, float _fY, float _fWidth, float _fHeight);
	
	// Render sprite.
	virtual void Render ();
		
public:
	
	IOGTexture*	m_pTexture;
	GLfloat		m_Vertices[20];
	GLuint		m_VBOHandle;
	MATRIX		m_mOrthoProj;
	GLfloat		m_fX, m_fY;
	GLfloat		m_fWidth;
	GLfloat		m_fHeight;
};


#endif
