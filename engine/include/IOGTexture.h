/*
 *  IOGTexture.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGTEXTURE_H_
#define IOGTEXTURE_H_


class IOGTexture
{
public:
	virtual ~IOGTexture () {}
		
	// get gl texture id
	virtual unsigned int GetTextureId () const = 0;
};

#endif
