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
#ifndef IOGGUIBUTTON_H_
#define IOGGUIBUTTON_H_

#include "IOGMath.h"
#include <string>
#include "IOGInputReceiver.h"


class IOGGuiButton
{
public:
	virtual ~IOGGuiButton() {}

	// Load graphics.
    virtual void Load (const std::string& _SprN, const std::string& _SprPr, const OGVec2& _Size) = 0;

	// Unload graphics.
    virtual void Unload () = 0;

	// Set button position.
    virtual void SetPosition (const OGVec2& _Pos) = 0;

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param) = 0;

	// Render sprite.
	virtual void Render () = 0;
};


#endif
