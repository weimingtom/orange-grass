/*
 *  OGLevelManager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "oglevelmanager.h"
#include "oglevel.h"


// constructor.
COGLevelManager::COGLevelManager ()
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
	if (!LoadConfig(cfg))
	{
		return false;
	}

	std::vector<Cfg::LevelCfg>::const_iterator iter = cfg.level_cfg_list.begin();
	for (; iter != cfg.level_cfg_list.end(); ++iter)
	{
		COGLevel* pLevel = new COGLevel ();
		pLevel->Init ((*iter).level_alias, (*iter).level_file);
		m_LevelList[(*iter).level_alias] = pLevel;
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
		lev_cfg.level_alias = m_pReader->ReadStringParam(pLevelNode, "terrain");
		lev_cfg.level_file = m_pReader->ReadStringParam(pLevelNode, "scene_file");
		lev_cfg.level_file = GetResourceMgr()->GetFullPath(lev_cfg.level_file);
		_cfg.level_cfg_list.push_back(lev_cfg);
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
    if (pLevel == NULL)
    {
        return NULL;
    }

    if (!pLevel->Load())
    {
        return NULL;
    }

    return pLevel;
}


// unload level.
void COGLevelManager::UnloadLevel (IOGLevel* _pLevel)
{
    COGLevel* pLevel = (COGLevel*)_pLevel;
	if (pLevel)
	{
		pLevel->Unload();
	}
}


// save level.
bool COGLevelManager::SaveLevel (IOGLevel* _pLevel)
{
    if (_pLevel == NULL)
        return false;

    return _pLevel->Save();
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
