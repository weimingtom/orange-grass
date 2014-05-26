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
#include "ogguiweaponpanel.h"


COGGuiWeaponPanel::COGGuiWeaponPanel ()
{
	m_pReader = GetSettingsReader();
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pWeapon = NULL;
}


COGGuiWeaponPanel::~COGGuiWeaponPanel()
{
    Unload();
}


// Load graphics.
void COGGuiWeaponPanel::Load (IOGGroupNode* _pNode)
{
	if (!_pNode)
		return;

	m_HUDSprStr = m_pReader->ReadStringParam(_pNode, "sprite");
	m_Position = m_pReader->ReadVec2Param(_pNode, "x", "y");
	m_Size = m_pReader->ReadVec2Param(_pNode, "width", "height");
	m_WeaponIconPos = m_pReader->ReadVec2Param(_pNode, "weapon_x", "weapon_y");
	m_WeaponIconSize = m_pReader->ReadVec2Param(_pNode, "weapon_width", "weapon_height");

    m_pFrame = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, m_HUDSprStr);
}


// Unload graphics.
void COGGuiWeaponPanel::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pFrame);
	m_pResourceMgr->ReleaseSprite(m_pWeapon);
}


// Update data.
void COGGuiWeaponPanel::UpdateData (const std::string& _SprWeapon)
{
    m_pWeapon = m_pResourceMgr->GetSprite(OG_RESPOOL_GAME, _SprWeapon);
}


// Render sprite.
void COGGuiWeaponPanel::Render ()
{
    m_pFrame->Render(m_Position, m_Size);
    if (m_pWeapon)
    {
        m_pWeapon->Render(m_Position + m_WeaponIconPos, m_WeaponIconSize);
    }
}


// Hit test.
bool COGGuiWeaponPanel::IsHit (const OGVec2& _vPos)
{
    if (_vPos.x >= m_Position.x && 
        _vPos.y >= m_Position.y &&
        _vPos.x <= m_Position.x + m_Size.x && 
        _vPos.y <= m_Position.y + m_Size.y)
	{
        return true;
    }
    return false;
}
