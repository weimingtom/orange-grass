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
#ifndef IOGSPRITE_H_
#define IOGSPRITE_H_

#include "IOGTexture.h"
#include "IOGMath.h"


class IOGSprite
{
public:
	virtual ~IOGSprite() {}

	// Initialize sprite.
	virtual void SetMapping (unsigned int _Mapping) = 0;
		
	// Render sprite.
	virtual void Render (const OGVec2& _vPos, const OGVec2& _vSize) = 0;
};


#endif
