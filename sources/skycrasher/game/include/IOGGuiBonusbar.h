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
#ifndef IOGGUIBONUSBAR_H_
#define IOGGUIBONUSBAR_H_

#include "IOGMath.h"
#include <string>
#include "IOGSettingsReader.h"


class IOGGuiBonusbar
{
public:
	virtual ~IOGGuiBonusbar() {}

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Update data.
	virtual void SetData (
        unsigned int _Id, 
        const std::string& _SprBonus, 
        unsigned int _Val, 
        unsigned int _MaxVal) = 0;

	// Render sprite.
	virtual void Render () = 0;

	// Reset data.
    virtual void ResetData () = 0;
};


#endif
