/*
 *  OGGuiWeaponPanel.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
#include "ogguiweaponpanel.h"


COGGuiWeaponPanel::COGGuiWeaponPanel ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pFrame = NULL;
    m_pWeapon = NULL;
}


COGGuiWeaponPanel::~COGGuiWeaponPanel()
{
    Unload();
}


// Load graphics.
void COGGuiWeaponPanel::Load ()
{
	m_Position = Vec2(420.0f, 260.0f);
	m_Size = Vec2(60.0f, 60.0f);

    m_pFrame = m_pResourceMgr->GetSprite("weapon_hud");
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
    m_pWeapon = m_pResourceMgr->GetSprite(_SprWeapon);
}


// Render sprite.
void COGGuiWeaponPanel::Render ()
{
    Vec2 vOffset = Vec2(-2.0f, 12.0f);
    Vec2 vSize = Vec2(64.0f, 36.0f);
    m_pFrame->Render(m_Position, m_Size);
    if (m_pWeapon)
    {
        m_pWeapon->Render(m_Position + vOffset, vSize);
    }
}


// Hit test.
bool COGGuiWeaponPanel::IsHit (const Vec2& _vPos)
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
