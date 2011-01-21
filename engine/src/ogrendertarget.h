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

	// apply texture
	virtual void Apply () const;
	
	// get texture width
	virtual unsigned int GetWidth () const { return m_Width; }
	
	// get texture height
	virtual unsigned int GetHeight () const { return m_Height; }
	
public:
	
	unsigned int	m_TextureId;
	unsigned int	m_Width;
	unsigned int	m_Height;
};

#endif
