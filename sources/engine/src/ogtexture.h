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

#include "IOGTexture.h"
#include "ogresource.h"
#include <vector>


class COGTexture : public IOGTexture, public COGResource
{
public:
	COGTexture ();
	virtual ~COGTexture ();
	
	// load from file.
	virtual bool Load ();

	// Unload resource.
	virtual void Unload ();

	// apply texture
	virtual void Apply () const;

	// get texture mapping
	virtual IOGMapping* GetMapping (unsigned int _Id);

	// get gl texture id
	virtual unsigned int GetTextureId () const { return m_TextureId; }
	
	// get texture width
	virtual unsigned int GetWidth () const { return m_Width; }
	
	// get texture height
	virtual unsigned int GetHeight () const { return m_Height; }

	// add texture mapping
	void AddMapping (IOGMapping* _pMapping);
	
private:
	
	unsigned int	m_TextureId;
	unsigned int	m_Width;
	unsigned int	m_Height;

	std::vector<IOGMapping*>	m_MappingsList;
};

#endif
