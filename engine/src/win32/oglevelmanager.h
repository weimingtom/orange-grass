/*
 *  OGLevelManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGLEVELMANAGER_H_
#define OGLEVELMANAGER_H_

#include "IOGLevelManager.h"
#include "oglevel.h"
#include <string>
#include <map>


class COGLevelManager : public IOGLevelManager
{
public:
	COGLevelManager ();
	virtual ~COGLevelManager ();

	// load from config file.
	virtual bool Init (const char* _pLevelCfgFile);
	
	// load level.
	virtual IOGLevel* LoadLevel (const char* _pAlias);
	
	// save level.
	virtual bool SaveLevel (IOGLevel* _pLevel);

	// get version.
    virtual unsigned int GetVersion () const { return LEVEL_VERSION; }

private:

    std::map<std::string, COGLevel*>	m_LevelList;
};


#endif
