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
#ifndef IOGGUIWEAPONPANEL_H_
#define IOGGUIWEAPONPANEL_H_

#include "IOGMath.h"
#include <string>
#include "IOGSettingsReader.h"


class IOGGuiWeaponPanel
{
public:
	virtual ~IOGGuiWeaponPanel() {}

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Update data.
	virtual void UpdateData (const std::string& _SprWeapon) = 0;

	// Render sprite.
	virtual void Render () = 0;

	// Hit test.
	virtual bool IsHit (const OGVec2& _vPos) = 0;
};


#endif
