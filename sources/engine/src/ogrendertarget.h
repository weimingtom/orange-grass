/*
 *  ogrendertarget.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 07.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
