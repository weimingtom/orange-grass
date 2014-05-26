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
#ifndef OGRENDERTARGET_H_
#define OGRENDERTARGET_H_


class COGRenderTarget
{
public:
    COGRenderTarget ();
    virtual ~COGRenderTarget ();

    // initialize render target
    virtual bool Init (bool _bColor, bool _bDepth, unsigned int _Width, unsigned int _Height, unsigned int _Border);

    // switch to render target
    virtual bool Begin ();

    // restore previous render target
    virtual void End ();

    // get texture width
    virtual unsigned int GetWidth () const { return m_Width; }

    // get texture height
    virtual unsigned int GetHeight () const { return m_Height; }

    // get color texture id
    virtual unsigned int GetColorTextureId () const { return m_ColorTextureId; }

    // get depth texture id
    virtual unsigned int GetDepthTextureId () const { return m_DepthTextureId; }

public:

    int m_OriginalFBO;
    unsigned int m_ColorTextureId;
    unsigned int m_DepthTextureId;
    unsigned int m_FBO;
    unsigned int m_Width;
    unsigned int m_Height;
    unsigned int m_Border;
};

#endif
