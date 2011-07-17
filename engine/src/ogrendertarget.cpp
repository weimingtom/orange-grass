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
	m_Size = 256;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OriginalFBO);

	// Generate and bind a render buffer which will become a depth buffer
	glGenRenderbuffers(1, &m_DepthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Size, m_Size);

    // Create a texture for rendering to
	glGenTextures(1, &m_TextureId);
	glBindTexture(GL_TEXTURE_2D, m_TextureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size, m_Size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	// Create the object that will allow us to render to the aforementioned texture
	glGenFramebuffers(1, &m_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferId);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, m_OriginalFBO);
}


COGRenderTarget::~COGRenderTarget ()
{
	glDeleteTextures(1, &m_TextureId);
	glDeleteFramebuffers(1, &m_FBO);
	glDeleteRenderbuffers(1, &m_DepthBufferId);

    m_TextureId = 0;
    m_DepthBufferId = 0;
    m_FBO = 0;
}


// switch to render target
void COGRenderTarget::Begin ()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OriginalFBO);

    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    glViewport(0, 0, m_Size, m_Size);
}


// restore previous render target
void COGRenderTarget::End ()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_OriginalFBO);
}
