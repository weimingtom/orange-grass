/*
 *  IOGLevelManager.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGLEVELMGR_H_
#define IOGLEVELMGR_H_

#include "IOGLevel.h"
#include <string>

#define LEVEL_VERSION   1


class IOGLevelManager
{
public:
	virtual ~IOGLevelManager () {}

	// load from config file.
	virtual bool Init () = 0;

	// load level.
	virtual IOGLevel* LoadLevel (const std::string& _Alias) = 0;

	// unload level.
	virtual void UnloadLevel (IOGLevel* _pLevel) = 0;

	// save level.
	virtual bool SaveLevel (IOGLevel* _pLevel) = 0;

	// get version.
	virtual unsigned int GetVersion () const = 0;
};

#endif
