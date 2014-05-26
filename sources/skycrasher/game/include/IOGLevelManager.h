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
#ifndef IOGLEVELMGR_H_
#define IOGLEVELMGR_H_

#include "IOGLevel.h"
#include <string>

#define LEVEL_VERSION   3


class IOGLevelManager
{
public:
	virtual ~IOGLevelManager () {}

	// load from config file.
	virtual bool Init () = 0;

	// load level.
	virtual IOGLevel* LoadLevel (const std::string& _Alias) = 0;

	// get currently loaded level.
	virtual IOGLevel* GetCurrentLevel () = 0;

	// unload level.
	virtual void UnloadLevel () = 0;

	// save level.
	virtual bool SaveLevel () = 0;

	// get level list (for editor).
	virtual void GetLevelList (std::vector<std::string>& _LevelList) const = 0;

	// get version.
	virtual unsigned int GetVersion () const = 0;
};

#endif
