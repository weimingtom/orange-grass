/*
 *  ogrendertarget.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "OpenGL2.h"
#include "ogrendertarget.h"


COGRenderTarget::COGRenderTarget () : m_TextureId (0)
{
}


COGRenderTarget::~COGRenderTarget ()
{
    glDeleteTextures(1, &m_TextureId);
    glDeleteFramebuffers(1, &m_FBO);

    m_TextureId = 0;
    m_FBO = 0;
}


// initialize render target
bool COGRenderTarget::Init (unsigned int _Size)
{
    m_Size = _Size;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OriginalFBO);

    // Create a texture for rendering to
    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Size, m_Size, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Size, m_Size, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Create the object that will allow us to render to the aforementioned texture
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_TextureId, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureId, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        OG_LOG_ERROR("Frame buffer is not complete");
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, m_OriginalFBO);
    return true;
}


// switch to render target
bool COGRenderTarget::Begin ()
{
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OriginalFBO);

    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        OG_LOG_ERROR("Frame buffer is not complete");
        return false;
    }

    //glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(1, 1, m_Size-2, m_Size-2);
    //glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);
    return true;
}


// restore previous render target
void COGRenderTarget::End ()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_OriginalFBO);
    //glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
}
