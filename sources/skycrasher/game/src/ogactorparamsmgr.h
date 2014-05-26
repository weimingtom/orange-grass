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
