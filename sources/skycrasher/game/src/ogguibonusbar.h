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
#ifndef OGGUIBONUSBAR_H_
#define OGGUIBONUSBAR_H_

#include "IOGGuiBonusbar.h"
#include <vector>


class COGGuiBonusbar : public IOGGuiBonusbar
{
public:
    COGGuiBonusbar ();
	virtual ~COGGuiBonusbar();

	// Load graphics.
    virtual void Load (IOGGroupNode* _pNode);

	// Unload graphics.
    virtual void Unload ();

	// Update data.
	virtual void SetData (
        unsigned int _Id, 
        const std::string& _SprBonus, 
        unsigned int _Val, 
        unsigned int _MaxVal);

	// Render sprite.
	virtual void Render ();

	// Reset data.
    virtual void ResetData ();

protected:

    struct BonusEntry
    {
        IOGSprite*      m_pBonus;
        unsigned int    m_Val; 
        unsigned int    m_MaxVal;
    };

protected:

	IOGSettingsReader*		m_pReader;
	IOGResourceMgr*	        m_pResourceMgr;
    IOGSprite*              m_pFrame;
    IOGSprite*              m_pCooldown;
    std::vector<BonusEntry> m_Entries;

	// UI layout settings
	std::string				m_PanelSprStr;
	std::string				m_BarSprStr;
    OGVec2                    m_Size;
    OGVec2                    m_Position;
    OGVec2					m_BonusIcoPos;
	OGVec2					m_BonusIcoSize;
    OGVec2					m_CoolDownBarPos;
	OGVec2					m_CoolDownBarSize;
	float					m_fVertInterval;
};


#endif
