/*
 * OrangeGrass
 * Copyright (C) 2009 Vyacheslav Bogdanov.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/lgpl-3.0-standalone.html>.
 */
#include "OrangeGrass.h"
#include "OpenGL2.h"
#include "ogrendertarget.h"


COGRenderTarget::COGRenderTarget () 
    : m_ColorTextureId (0)
    , m_DepthTextureId (0)
    , m_Width (0)
    , m_Height (0)
    , m_Border (0)
    , m_FBO(0)
    , m_OriginalFBO(0)
{
}


COGRenderTarget::~COGRenderTarget ()
{
    if (m_ColorTextureId)
        glDeleteTextures(1, &m_ColorTextureId);
    if (m_DepthTextureId)
        glDeleteTextures(1, &m_DepthTextureId);
    if (m_FBO)
        glDeleteFramebuffers(1, &m_FBO);
}


// initialize render target
bool COGRenderTarget::Init (bool _bColor, bool _bDepth, unsigned int _Width, unsigned int _Height, unsigned int _Border)
{
    m_Width = _Width;
    m_Height = _Height;
    m_Border = _Border;

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_OriginalFBO);

    // Create textures for rendering to
    if (_bColor)
    {
        glGenTextures(1, &m_ColorTextureId);
        glBindTexture(GL_TEXTURE_2D, m_ColorTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    if (_bDepth)
    {
        glGenTextures(1, &m_DepthTextureId);
        glBindTexture(GL_TEXTURE_2D, m_DepthTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    // Create the frame buffer object
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    if (_bColor)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorTextureId, 0);
    }
    if (_bDepth)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_DepthTextureId, 0);
    }

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

    GLbitfield clearMask = 0;
    GLboolean colorMask = GL_FALSE;
    GLboolean depthMask = GL_FALSE;
    if (m_ColorTextureId)
    {
        colorMask = GL_TRUE;
        clearMask |= GL_COLOR_BUFFER_BIT;
    }
    if (m_DepthTextureId)
    {
        depthMask = GL_TRUE;
        clearMask |= GL_DEPTH_BUFFER_BIT;
    }
    glClear(clearMask);
    glViewport(m_Border, m_Border, m_Width-m_Border*2, m_Height-m_Border*2);
    glColorMask(colorMask, colorMask, colorMask, colorMask);
    glDepthMask(depthMask);
    return true;
}


// restore previous render target
void COGRenderTarget::End ()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_OriginalFBO);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);
}
