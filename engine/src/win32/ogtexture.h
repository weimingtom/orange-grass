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

#include "OpenGL2.h"
#include "IOGTexture.h"
#include "Graphics.h"
#include "Geometry.h"
#include "Mathematics.h"
#include "ogresource.h"


class COGTexture : public IOGTexture, public COGResource
{
public:
	COGTexture ();
	virtual ~COGTexture ();
	
	// load from file.
	virtual bool Load ();
	
	// get gl texture id
	virtual unsigned int GetTextureId () const { return m_TextureId; }
	
private:
	
	// Texture handle
	GLuint			m_TextureId;
	CTexture*		m_pTexture;	
};

#endif
