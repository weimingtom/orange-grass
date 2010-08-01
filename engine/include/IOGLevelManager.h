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


class IOGLevelManager
{
public:
	virtual ~IOGLevelManager () {}
		
	// load from config file.
	virtual bool Init (const char* _pLevelCfgFile) = 0;
	
	// load level.
	virtual IOGLevel* LoadLevel (const char* _pAlias) = 0;
};

#endif
