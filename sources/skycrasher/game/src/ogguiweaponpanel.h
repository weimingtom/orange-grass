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
#ifndef OGGUIWEAPONPANEL_H_
#define OGGUIWEAPONPANEL_H_

#include "IOGGuiWeaponPanel.h"


class COGGuiWeaponPanel :   public IOGGuiWeaponPanel
{
public:
    COGGuiWeaponPanel ();
	virtual ~COGGuiWeaponPanel();

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode);

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void UpdateData (const std::string& _SprWeapon);

	// Render sprite.
	virtual void Render ();

	// Hit test.
	virtual bool IsHit (const OGVec2& _vPos);

protected:

	IOGSettingsReader*	m_pReader;
	IOGResourceMgr*		m_pResourceMgr;
    IOGSprite*			m_pFrame;
    IOGSprite*			m_pWeapon;

	// UI layout settings
	std::string			m_HUDSprStr;
	OGVec2				m_Size;
    OGVec2				m_Position;
	OGVec2				m_WeaponIconPos;
	OGVec2				m_WeaponIconSize;
};


#endif
