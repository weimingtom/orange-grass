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

	// switch to render target
	virtual void Begin ();

	// restore previous render target
	virtual void End ();
	
	// get texture size
	virtual unsigned int GetSize () const { return m_Size; }
	
	// get texture id
	virtual unsigned int GetTextureId () const { return m_TextureId; }
	
public:
	
    int m_OriginalFBO;
	unsigned int m_TextureId;
    unsigned int m_DepthBufferId;
    unsigned int m_FBO;
	unsigned int m_Size;
};

#endif
