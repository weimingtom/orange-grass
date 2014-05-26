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
#include "Game.h"
#include "oglevelmanager.h"
#include "oglevel.h"


// constructor.
COGLevelManager::COGLevelManager () : m_pCurLevel(NULL)
{
	m_pReader = GetSettingsReader();
}


// destructor.
COGLevelManager::~COGLevelManager ()
{
}


// load from config file.
bool COGLevelManager::Init ()
{
	Cfg cfg;
	cfg.level_cfg_list.reserve(16);
	if (!LoadConfig(cfg))
	{
		return false;
	}

    return true;
}


// Load level manager configuration
bool COGLevelManager::LoadConfig (COGLevelManager::Cfg& _cfg)
{
	IOGSettingsSource* pSource = m_pReader->OpenSource(GetResourceMgr()->GetFullPath("levels.xml"));
	if (!pSource)
		return false;

	IOGGroupNode* pRoot = m_pReader->OpenGroupNode(pSource, NULL, "Levels");
	IOGGroupNode* pLevelNode = m_pReader->OpenGroupNode(pSource, pRoot, "Level");
	for (; pLevelNode != NULL; )
	{
		Cfg::LevelCfg lev_cfg;
		lev_cfg.alias = m_pReader->ReadStringParam(pLevelNode, "alias");
		lev_cfg.file = GetResourceMgr()->GetFullPath(m_pReader->ReadStringParam(pLevelNode, "file"));
		_cfg.level_cfg_list.push_back(lev_cfg);

		COGLevel* pLevel = new COGLevel ();
		pLevel->Init (lev_cfg.alias, lev_cfg.file);
		m_LevelList[lev_cfg.alias] = pLevel;

		pLevelNode = m_pReader->ReadNextNode(pLevelNode);
	}
	m_pReader->CloseGroupNode(pRoot);
	m_pReader->CloseSource(pSource);
	return true;
}


// load level.
IOGLevel* COGLevelManager::LoadLevel (const std::string& _Alias)
{
	COGLevel* pLevel = m_LevelList[_Alias];
    if (pLevel)
    {
		switch (pLevel->GetLoadState())
		{
			case OG_RESSTATE_LOADED:
                m_pCurLevel = pLevel;
				return pLevel;

			case OG_RESSTATE_DEFINED:
				if (pLevel->Load() == false)
					return NULL;
                m_pCurLevel = pLevel;
				return pLevel;

			default:
				return NULL;
		}
    }
    return NULL;
}


// unload level.
void COGLevelManager::UnloadLevel ()
{
	if (m_pCurLevel)
	{
		m_pCurLevel->Unload();
	}
}


// save level.
bool COGLevelManager::SaveLevel ()
{
    if (m_pCurLevel == NULL)
        return false;

    return m_pCurLevel->Save();
}


// get level list (for editor).
void COGLevelManager::GetLevelList (std::vector<std::string>& _LevelList) const
{
	std::map<std::string, COGLevel*>::const_iterator iter = m_LevelList.begin();
	for (; iter != m_LevelList.end(); ++iter)
	{
		_LevelList.push_back(iter->first);
	}
}
