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
#ifndef OGGUIBUTTON_H_
#define OGGUIBUTTON_H_

#include "IOGGuiButton.h"


class COGGuiButton : public IOGGuiButton
{
public:
    COGGuiButton ();
	virtual ~COGGuiButton();

	// Load graphics.
    virtual void Load (const std::string& _SprN, const std::string& _SprPr, const OGVec2& _Size);

	// Unload graphics.
    virtual void Unload ();

	// Set button position.
    virtual void SetPosition (const OGVec2& _Pos);

	// Touch event handler.
	virtual bool OnTouch (const OGVec2& _vPos, IOGTouchParam _param);

	// Render sprite.
	virtual void Render ();

protected:

	IOGResourceMgr*	m_pResourceMgr;
    IOGSprite*      m_pNormal;
    IOGSprite*      m_pPressed;
    IOGSprite*      m_pCurSpr;
    OGVec2            m_Size;
    OGVec2            m_Position;
};


#endif
