/*
 *  OGActorParamsMgr.h
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 12.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef OGACTORPARAMSMGR_H_
#define OGACTORPARAMSMGR_H_

#include "IOGActorParamsManager.h"
#include <map>
#include "IOGSettingsReader.h"


class COGActorParamsMgr : public IOGActorParamsMgr
{
public:
	COGActorParamsMgr ();
	virtual ~COGActorParamsMgr ();

	// load from config file.
	virtual bool Init ();
	
	// get params by alias.
	virtual IOGActorParams* GetParams (const std::string& _Alias);

	// get params list.
	virtual void GetParamsList (std::list<IOGActorParams*>& _List);

private:

	// Load actor params configuration
	bool LoadParamsConfig (const std::string& _Alias, const std::string& _Path);

private:

    std::map<std::string, IOGActorParams*>	m_ParamsList;
	IOGSettingsReader*	m_pReader;
};

#endif
