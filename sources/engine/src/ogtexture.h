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
