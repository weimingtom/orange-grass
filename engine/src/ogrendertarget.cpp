/*
 *  ogrendertarget.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OpenGL2.h"
#include "GraphicsDevice.h"
#include "ogrendertarget.h"


COGRenderTarget::COGRenderTarget () : m_TextureId (0)
{
	m_Width = 256;
	m_Height = 256;

	// Bind and Enable Texture ID
	glGenTextures(1, &m_TextureId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glEnable(GL_TEXTURE_2D);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,0);
}


COGRenderTarget::~COGRenderTarget ()
{
	glDeleteTextures(1, &m_TextureId);
	m_TextureId = 0;
}


// apply texture
void COGRenderTarget::Apply () const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, m_Width, m_Height, 0);
}
