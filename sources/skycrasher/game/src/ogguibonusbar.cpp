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
#include "Game.h"
#include "ogguibonusbar.h"


COGGuiBonusbar::COGGuiBonusbar ()
{
	m_pReader = GetSettingsReader();
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pCooldown = NULL;

    m_Entries.reserve(4);
    for (int i = 0; i < 4; ++i)
    {
        BonusEntry bonus;
        bonus.m_MaxVal = 0;
        bonus.m_Val = 0;
        bonus.m_pBonus = NULL;
        m_Entries.push_back(bonus);
    }
}


COGGuiBonusbar::~COGGuiBonusbar()
{
    Unload();
}


// Load graphics.
void COGGuiBonusbar::Load (IOGGroupNode* _pNode)
{
	if (!_pNode)
		return;

	m_PanelSprStr = m_pReader->ReadStringParam(_pNode, "panel_sprite");
	m_BarSprStr = m_pReader->ReadStringParam(_pNode, "bar_sprite");
	m_Position = m_pReader->ReadVec2Param(_pNode, "x", "y");
	m_Size = m_pReader->ReadVec2Param(_pNode, "width", "height");
	m_CoolDownBarPos = m_pReader->ReadVec2Param(_pNode, "bar_x", "bar_y");
	m_CoolDownBarSize = m_pReader->ReadVec2Param(_pNode, "bar_width", "bar_height");
	m_BonusIcoPos = m_pReader->ReadVec2Param(_pNode, "bonus_x", "bonus_y");
	m_BonusIcoSize = m_pReader->ReadVec2Param(_pNode, "bonus_width", "bonus_height");
	m_fVertInterval = m_pReader->ReadFloatParam(_pNode, "vert_interval");

	m_pFrame = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, m_PanelSprStr);
    m_pCooldown = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, m_BarSprStr);
}


// Unload graphics.
void COGGuiBonusbar::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pFrame);
	m_pResourceMgr->ReleaseSprite(m_pCooldown);
}


// Update data.
void COGGuiBonusbar::SetData (unsigned int _Id, 
                              const std::string& _SprBonus, 
                              unsigned int _Val, 
                              unsigned int _MaxVal)
{
    BonusEntry& bonus = m_Entries[_Id];
    bonus.m_MaxVal = _MaxVal;
    bonus.m_Val = _Val;
    bonus.m_pBonus = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, _SprBonus);
}


// Render sprite.
void COGGuiBonusbar::Render ()
{
    unsigned int NumEntries = m_Entries.size();
    for (unsigned int i = 0; i < NumEntries; ++i)
    {
        BonusEntry& bonus = m_Entries[i];
        if (bonus.m_pBonus)
        {
            OGVec2 vPos = m_Position + OGVec2(0, (m_Size.y + m_fVertInterval) * i);
            m_pFrame->Render(m_Position + OGVec2(0, (m_Size.y + m_fVertInterval) * i), m_Size);
            bonus.m_pBonus->Render(vPos + m_BonusIcoPos, m_BonusIcoSize);
            if (bonus.m_MaxVal > 0)
            {
                float fPercent = (float)bonus.m_Val / (float)bonus.m_MaxVal;
                m_pCooldown->Render(vPos + m_CoolDownBarPos, OGVec2(m_CoolDownBarSize.x * fPercent, m_CoolDownBarSize.y));
            }
        }
    }
}


// Reset data.
void COGGuiBonusbar::ResetData ()
{
    unsigned int NumEntries = m_Entries.size();
    for (unsigned int i = 0; i < NumEntries; ++i)
    {
        BonusEntry& bonus = m_Entries[i];
        bonus.m_pBonus = NULL;
        bonus.m_Val = bonus.m_MaxVal = 0;
    }
}
