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

	// get weapon params by alias.
	virtual IOGWeaponParams* GetWeaponParams (const std::string& _Alias) = 0;

	// get bonus params by alias.
	virtual IOGBonusParams* GetBonusParams (const std::string& _Alias) = 0;

	// get params list.
	virtual void GetParamsList (std::list<IOGActorParams*>& _List) = 0;
};

#endif
