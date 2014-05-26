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
#ifndef IOGAPPSETTINGS_H_
#define IOGAPPSETTINGS_H_

#include <string>


class IOGAppSettings
{
public:
	virtual ~IOGAppSettings() {}

	// read settings file.
	virtual bool Init (const std::string& _File) = 0;

	// read screen mode settings file.
	virtual bool InitScreenMode () = 0;
};


#endif
