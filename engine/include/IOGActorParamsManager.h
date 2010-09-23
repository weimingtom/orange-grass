/*
 *  IOGActorParamsMgr.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef IOGACTORPARAMSMGR_H_
#define IOGACTORPARAMSMGR_H_

#include "IOGActorParams.h"
#include <list>


class IOGActorParamsMgr
{
public:
	virtual ~IOGActorParamsMgr () {}

	// load from config file.
	virtual bool Init () = 0;
	
	// get params by alias.
	virtual IOGActorParams* GetParams (const std::string& _Alias) = 0;

	// get params list.
	virtual void GetParamsList (std::list<IOGActorParams*>& _List) = 0;
};

#endif
