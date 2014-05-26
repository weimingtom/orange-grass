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
#ifndef OGLEVELMANAGER_H_
#define OGLEVELMANAGER_H_

#include "IOGLevelManager.h"
#include "oglevel.h"
#include <string>
#include <map>
#include "IOGSettingsReader.h"


class COGLevelManager : public IOGLevelManager
{
public:
	COGLevelManager ();
	virtual ~COGLevelManager ();

	// load from config file.
	virtual bool Init ();
	
	// load level.
	virtual IOGLevel* LoadLevel (const std::string& _Alias);

	// get currently loaded level.
    virtual IOGLevel* GetCurrentLevel () { return m_pCurLevel; }

	// unload level.
	virtual void UnloadLevel ();
	
	// save level.
	virtual bool SaveLevel ();

	// get level list (for editor).
	virtual void GetLevelList (std::vector<std::string>& _LevelList) const;

	// get version.
    virtual unsigned int GetVersion () const { return LEVEL_VERSION; }

private:

	struct Cfg
	{
		struct LevelCfg
		{
			std::string alias;
			std::string file;
		};

		std::vector<LevelCfg> level_cfg_list;
	};

	// Load level manager configuration
	bool LoadConfig (COGLevelManager::Cfg& _cfg);

private:

	IOGSettingsReader*	m_pReader;
    std::map<std::string, COGLevel*>	m_LevelList;
    COGLevel* m_pCurLevel;
};


#endif
