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
#include "ogguibutton.h"


COGGuiButton::COGGuiButton ()
{
	m_pResourceMgr = GetResourceMgr();
    m_pNormal = NULL;
    m_pPressed = NULL;
    m_pCurSpr = NULL;
}


COGGuiButton::~COGGuiButton()
{
    Unload();
}


// Load graphics.
void COGGuiButton::Load (const std::string& _SprN, const std::string& _SprPr, const OGVec2& _Size)
{
    m_pNormal = m_pResourceMgr->GetSprite(OG_RESPOOL_UI, _SprN);
    m_pPressed = m_pResourceMgr->GetSprite(OG_RESPOOL_UI, _SprPr);
    m_pCurSpr = m_pNormal;
    m_Size = _Size;
}


// Unload graphics.
void COGGuiButton::Unload ()
{
	m_pResourceMgr->ReleaseSprite(m_pNormal);
	m_pResourceMgr->ReleaseSprite(m_pPressed);
    m_pCurSpr = NULL;
}


// Set button position.
void COGGuiButton::SetPosition (const OGVec2& _Pos)
{
    m_Position = _Pos;
}


// Touch event handler.
bool COGGuiButton::OnTouch (const OGVec2& _vPos, IOGTouchParam _param)
{
    if (_param == OG_TOUCH_UP)
    {
        m_pCurSpr = m_pNormal;
    }

    if (_vPos.x >= m_Position.x && 
        _vPos.y >= m_Position.y &&
        _vPos.x <= m_Position.x + m_Size.x && 
        _vPos.y <= m_Position.y + m_Size.y)
    {
        if (_param == OG_TOUCH_DOWN)
        {
            m_pCurSpr = m_pPressed;
        }
        return true;
    }
    return false;
}


// Render sprite.
void COGGuiButton::Render ()
{
    if (m_pCurSpr)
    {
    	m_pCurSpr->Render(m_Position, m_Size);
    }
}
