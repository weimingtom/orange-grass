/*
 *  OGGuiWeaponPanel.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
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
