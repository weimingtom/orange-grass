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
#ifndef OGAPPSETTINGS_H_
#define OGAPPSETTINGS_H_

#include "IOGAppSettings.h"
#include "IOGSettingsReader.h"
#include "IOGGlobalVarsTable.h"


class COGAppSettings : public IOGAppSettings
{
public:
	COGAppSettings();
	virtual ~COGAppSettings();

	// read settings file.
	virtual bool Init (const std::string& _File);

	// read screen mode settings file.
	virtual bool InitScreenMode ();

private:

	bool				m_bInitialized;
	IOGSettingsReader*	m_pReader;
	IOGGlobalVarsTable*	m_pGlobalVars;
};


#endif
