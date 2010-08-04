/*
 *  OGLevelManager.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#define _CRT_SECURE_NO_WARNINGS
#include "OrangeGrass.h"
#include "oglevelmanager.h"
#include "oglevel.h"
#include "Pathes.h"
#include "tinyxml.h"


// constructor.
COGLevelManager::COGLevelManager ()
{
}


// destructor.
COGLevelManager::~COGLevelManager ()
{
}


// load from config file.
bool COGLevelManager::Init (const char* _pLevelCfgFile)
{
    char file_path[2048];
    sprintf(file_path, "%s\\%s", GetResourceMgr()->GetResourcePath(), _pLevelCfgFile);

    TiXmlDocument* pXmlSettings = new TiXmlDocument ("levels.xml");
    if (!pXmlSettings->LoadFile (file_path))
        return false;
    TiXmlHandle* hDoc = new TiXmlHandle (pXmlSettings);

    int index = 0;
    TiXmlHandle hTerrainsRoot = hDoc->FirstChild ( "Levels" );
    TiXmlHandle TerrainHandle = hTerrainsRoot.Child ( "Level", index );
    while (TerrainHandle.Node ())
    {
        TiXmlElement* pElement = TerrainHandle.Element();
        const char* level_alias = pElement->Attribute ("terrain");
        const char* level_file = pElement->Attribute ("scene_file");
        sprintf(file_path, "%s\\%s", GetResourceMgr()->GetResourcePath(), level_file);
        COGLevel* pLevel = new COGLevel ();
        pLevel->Init (level_alias, file_path);
        m_LevelList[level_alias] = pLevel;
        TerrainHandle = hTerrainsRoot.Child ( "Level", ++index );
    }

    return true;
}


// load level.
IOGLevel* COGLevelManager::LoadLevel (const char* _pAlias)
{
    COGLevel* pLevel = m_LevelList[_pAlias];
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
