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
#ifndef IOGFOG_H_
#define IOGFOG_H_

#include "IOGMath.h"


class IOGFog
{
public:
	virtual ~IOGFog () {}

	// set light color.
	virtual void SetColor (const OGVec4& _vColor) = 0;
	
	// get light color.
	virtual const OGVec4& GetColor () const = 0;

	// set fog start.
	virtual void SetStart (float _fStart) = 0;

	// set fog end.
	virtual void SetEnd (float _fEnd) = 0;

	// set fog density.
	virtual void SetDensity (float _fDensity) = 0;

	// set fog enabled status.
	virtual void SetEnabled (bool _bEnable) = 0;

	// get fog start.
	virtual float GetStart () const = 0;

	// get fog end.
	virtual float GetEnd () const = 0;

	// get fog density.
	virtual float GetDensity () const = 0;

	// get fog enabled status.
	virtual bool IsEnabled () const = 0;
};

#endif
