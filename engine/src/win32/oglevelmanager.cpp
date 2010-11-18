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
				return pLevel;

			case OG_RESSTATE_DEFINED:
				if (pLevel->Load() == false)
					return NULL;
				return pLevel;

			default:
				return NULL;
		}
    }
    return NULL;
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
