/*
 *  OGGuiButton.cpp
 *  OrangeGrass
 *
 *  Created by Viacheslav Bogdanov on 11.11.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include "OrangeGrass.h"
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
