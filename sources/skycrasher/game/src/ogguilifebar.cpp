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
#include "ogguilifebar.h"


COGGuiLifebar::COGGuiLifebar ()
{
	m_pReader = GetSettingsReader();
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pBar = NULL;

    m_Val = 0;
    m_MaxVal = 0;
}


COGGuiLifebar::~COGGuiLifebar()
{
    Unload();
}


// Load graphics.
void COGGuiLifebar::Load (IOGGroupNode* _pNode)
{
	if (!_pNode)
		return;

	m_PanelSprStr = m_pReader->ReadStringParam(_pNode, "panel_sprite");
	m_BarSprStr = m_pReader->ReadStringParam(_pNode, "bar_sprite");
	m_Position = m_pReader->ReadVec2Param(_pNode, "x", "y");
	m_Size = m_pReader->ReadVec2Param(_pNode, "width", "height");
	m_BarPos = m_pReader->ReadVec2Param(_pNode, "bar_x", "bar_y");
	m_BarSize = m_pReader->ReadVec2Param(_pNode, "bar_width", "bar_height");
	m_MaxBars = m_pReader->ReadIntParam(_pNode, "max_bars");

	m_pFrame = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, m_PanelSprStr);
    m_pBar = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, m_BarSprStr);
}


// Unload graphics.
void COGGuiLifebar::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pFrame);
	m_pResourceMgr->ReleaseSprite(m_pBar);
}


// Update data.
void COGGuiLifebar::UpdateData (unsigned int _Val, unsigned int _MaxVal)
{
    m_Val = _Val;
    m_MaxVal = _MaxVal;
}


// Render sprite.
void COGGuiLifebar::Render ()
{
    float fLifePercent = (float)m_Val / (float)m_MaxVal;
    unsigned int NumBars = (unsigned int)(fLifePercent * m_MaxBars);

    for (unsigned int i = 0; i < NumBars; ++i)
    {
		float fBarHeight = m_BarSize.y;
        if (i == 41 || i == 40)
        {
            fBarHeight = 14.0f;
        }
        m_pBar->Render(m_Position + OGVec2(m_BarPos.x + i * (m_BarSize.x + 1), m_BarPos.y), OGVec2(m_BarSize.x, fBarHeight));
    }

    m_pFrame->Render(m_Position, m_Size);

}
