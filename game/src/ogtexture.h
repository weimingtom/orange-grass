/*
 *  ogtexture.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGTEXTURE_H_
#define OGTEXTURE_H_

#include "IOGTexture.h"
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#include "common.h"
#include "GraphicsDevice.h"
#include "Geometry.h"
#include "Mathematics.h"


class COGTexture : public IOGTexture
{
public:
	COGTexture ();
	virtual ~COGTexture ();
	
	// load from file.
	virtual bool LoadFromFile (const char* _pTextureFile);
	
	// get gl texture id
	virtual unsigned int GetTextureId () const { return m_TextureId; }
	
private:
	
	// Texture handle
	GLuint			m_TextureId;
	CTexture*		m_pTexture;	
};

#endif
