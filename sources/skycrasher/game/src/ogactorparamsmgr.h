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

	// get weapon params by alias.
	virtual IOGWeaponParams* GetWeaponParams (const std::string& _Alias);

	// get bonus params by alias.
	virtual IOGBonusParams* GetBonusParams (const std::string& _Alias);

	// get params list.
	virtual void GetParamsList (std::list<IOGActorParams*>& _List);

private:

	// load from config file.
	virtual bool InitWeaponParams ();

	// load from config file.
	virtual bool InitBonusParams ();

	// load from config file.
	virtual bool InitActorParams ();

	// Load actor params configuration
	bool LoadParamsConfig (const std::string& _Alias, const std::string& _Path);

	// Load weapon params configuration
	bool LoadWeaponParamsConfig (const std::string& _Alias, const std::string& _Path);

	// Load bonus params configuration
	bool LoadBonusParamsConfig (const std::string& _Alias, const std::string& _Path);

private:

	IOGSettingsReader*	m_pReader;

    std::map<std::string, IOGActorParams*>	m_ParamsList;
    std::map<std::string, IOGWeaponParams*> m_WeaponParamsList;
    std::map<std::string, IOGBonusParams*>	m_BonusParamsList;
};

#endif
