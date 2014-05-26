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
#ifndef IOGLEVEL_H_
#define IOGLEVEL_H_

#include "IOGModel.h"


class IOGLevel
{
public:
	virtual ~IOGLevel () {}
		
	// get associated terrain.
	virtual IOGModel* GetTerrain () = 0;

	// get level start position.
	virtual const OGVec3& GetStartPosition () const = 0;

	// get level start finish.
	virtual const OGVec3& GetFinishPosition () const = 0;

	// get level active width.
	virtual float GetActiveWidth () const = 0;

	// set level start position.
	virtual void SetStartPosition (const OGVec3& _Pos) = 0;

	// set level start finish.
	virtual void SetFinishPosition (const OGVec3& _Pos) = 0;

	// set level active width.
	virtual void SetActiveWidth (float _fWidth) = 0;
	
	// save level.
	virtual bool Save () = 0;
};

#endif
